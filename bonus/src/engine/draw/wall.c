/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:03:04 by escura            #+#    #+#             */
/*   Updated: 2024/10/01 13:46:03 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	vert_offset(const t_player *p)
{
	return ((p->z_dir) * HEIGHT);
}

t_texture	*get_wall_side(int side, const t_textures *texs, int n)
{
	t_texture	*t;

	t = NULL;
	if (side == 1)
		t = texs->wall_south[n];
	else if (side == 2)
		t = texs->wall_east[n];
	else if (side == 3)
		t = texs->wall_north[n];
	else if (side == 4)
		t = texs->wall_west[n];
	else if (side == 5)
		t = texs->door;
	else if (side == 6)
		t = texs->wall_west[n];
	else if (side == 7)
		t = texs->wall_south[n];
	else
		return (NULL);
	return (t);
}

float	view_current_distance(const t_player *p, int start_y, float angle)
{
	float	z;
	float	current_dist;

	z = 1;
	if (start_y >= HEIGHT / 2)
		z = 0;
	current_dist = (p->z - z) * HEIGHT / (start_y - HEIGHT / 2);
	return (current_dist / cos(angle - p->angle));
}

t_texture	*get_texture(int start_y, int height, const t_player *p,
		const t_textures *texs)
{
	if (start_y > HEIGHT / 2 + (p->z * height))
	{
		return (texs->floor[player()->level]);
	}
	else if (start_y < ((p->z * height) + HEIGHT / 2) - height)
	{
		return (texs->ceiling[player()->level]);
	}
	return (NULL);
}

int	darken_color(int color, float dist)
{
	int	r;
	int	g;
	int	b;
	int	factor;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	factor = (int)((1.0f - dist) * 255);
	r = (r * factor) >> 8;
	g = (g * factor) >> 8;
	b = (b * factor) >> 8;
	return ((r << 16) | (g << 8) | b);
}

int	darken_color_wall(int color, float factor, float wall_x, float wall_y)
{
	t_sprite	*torches;
	int			i;
	float		dist_to_torch;
	float		total_darken_factor;
	float		torch_darken_factor;
	float		darken_factor;

	torches = cube()->map->facing;
	// return(color);
	if (torches[0].x == -1)
		return (color = darken_color(color, factor));
	if (torches[0].x != -1)
	{
		i = 0;
		float torch_x, torch_y;
		total_darken_factor = 1.0f;
		while (torches[i].x != -1)
		{
			torch_x = torches[i].x;
			torch_y = torches[i].y;
			dist_to_torch = distance(wall_x, wall_y, torch_x, torch_y);
			torch_darken_factor = dist_to_torch / 2.0f;
			darken_factor = fminf(torch_darken_factor, factor);
			total_darken_factor = fminf(total_darken_factor, darken_factor);
			i++;
		}
		total_darken_factor = fminf(total_darken_factor, 1.0f);
		color = darken_color(color, total_darken_factor);
	}
	return (color);
}

int	get_texture_color(t_texture *tex, float dist, float cosangle,
		float sinangle)
{
	float	tex_x;
	float	tex_y;
	int		color;

	tex_x = player()->x + dist * cosangle;
	tex_y = player()->y + dist * sinangle;
	color = get_pixel_from_image(tex, tex_x * T_SIZE, tex_y * T_SIZE);
	color = darken_color_wall(color, (float)dist / 7, tex_x, tex_y);
	return (color);
}

void	draw_scene(t_draw *draw, ThreadParams *params)
{
	int					height;
	int					start_x;
	const t_player		*p = params->player;
	const t_textures	*texs = params->textures;
	t_render			*r;
	float				cosangle;
	float				sinangle;
	bool				catched;
	t_texture			*wall_side;
	float				tex_y;
	float				step;
	int					wall_start_y;
	int					wall_end_y;
	int					color;
	int					y;
	t_texture			*tex;
	float				current_dist;

	height = draw->wall_height;
	start_x = draw->start_x;
	r = params->render;
	cosangle = cos(draw->angle);
	sinangle = sin(draw->angle);
	catched = p->catch && draw->side == 6;
	wall_side = get_wall_side(draw->side, texs, p->level);
	tex_y = 0;
	step = (float)T_SIZE / draw->wall_height;
	wall_start_y = (p->z - 1) * draw->wall_height + vert_offset(p);
	wall_end_y = wall_start_y + draw->wall_height;
	if (wall_start_y < 0)
	{
		tex_y = step * (-wall_start_y);
		wall_start_y = 0;
	}
	if (wall_end_y > HEIGHT)
		wall_end_y = HEIGHT;
	color = 0;
	y = 0;
	while (y < HEIGHT)
	{
		if (y >= wall_end_y || y < wall_start_y)
		{
			tex = get_texture(y, height, p, texs);
			if (tex)
			{
				current_dist = view_current_distance(p, y, draw->angle);
				color = get_texture_color(tex, current_dist, cosangle,
						sinangle);
				if (color < 0)
					color = 0;
			}
		}
		else
		{
			if (catched)
			{
				color = 255;
				color = darken_color(color, (float)draw->dist / 350);
			}
			else
			{
				color = get_pixel_from_image(wall_side, draw->tex_x, tex_y);
				color = darken_color_wall(color, (float)draw->dist / 450,
						draw->x / BLOCK_SIZE, draw->y / BLOCK_SIZE);
			}
			if (color < 0)
				color = 0;
			tex_y += step;
		}
		y++;
		draw->colors[y] = color;
	}
}
