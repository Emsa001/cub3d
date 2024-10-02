/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:03:04 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 21:24:07 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	vert_offset(const t_player *p)
{
	return ((p->z_dir) * HEIGHT);
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

t_texture	*get_texture(int start_y, int height, t_thread_params *p)
{
	if (start_y > HEIGHT / 2 + (p->player->z * height))
	{
		return (p->textures->floor[player()->level]);
	}
	else if (start_y < ((p->player->z * height) + HEIGHT / 2) - height)
	{
		return (p->textures->ceiling[player()->level]);
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

int	get_texture_color(t_texture *tex, float dist, t_draw *draw)
{
	float	tex_x;
	float	tex_y;
	int		color;

	tex_x = player()->x + dist * draw->cosangle;
	tex_y = player()->y + dist * draw->sinangle;
	color = get_pixel_from_image(tex, tex_x * T_SIZE, tex_y * T_SIZE);
	color = darken_color_wall(color, (float)dist / 7, tex_x, tex_y);
	return (color);
}
