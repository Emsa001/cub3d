/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:46:18 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 21:52:51 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_draw *draw, t_thread_params *params, int start_y)
{
	float		current_dist;
	t_texture	*tex;
	int			color;

	if (params->player->z > 1)
		return ;
	while (start_y >= 0)
	{
		if (draw->colors[start_y] == 0)
		{
			current_dist = view_current_distance(params->player, start_y,
					draw->angle);
			tex = params->textures->ceiling[params->player->level];
			color = get_texture_color(tex, current_dist, draw);
			if (color <= 0)
				color = 0;
			draw->colors[start_y] = color;
		}
		start_y--;
	}
}

static void	draw_wall(t_draw *draw, int start_y, int end_y)
{
	int		color;
	float	step;

	if (start_y < 0)
		start_y = 0;
	step = ((float)T_SIZE) / draw->height;
	while (start_y <= end_y)
	{
		if (draw->colors[start_y] == 0)
		{
			color = get_pixel_from_image(draw->texture, draw->tex_x,
					draw->tex_y);
			color = darken_color_wall(color, (float)draw->dist / 450, draw->x
					/ BLOCK_SIZE, draw->y / BLOCK_SIZE);
			if (color <= 0)
				color = 0;
			draw->tex_y += step;
			draw->colors[start_y] = color;
		}
		start_y++;
	}
}

void	draw_floor(t_draw *draw, t_thread_params *params, int end_y)
{
	float		current_dist;
	t_texture	*tex;
	int			color;

	if (params->player->z < 0)
		return ;
	while (end_y < HEIGHT)
	{
		if (draw->colors[end_y] == 0)
		{
			current_dist = view_current_distance(params->player, end_y,
					draw->angle);
			tex = params->textures->floor[params->player->level];
			color = get_texture_color(tex, current_dist, draw);
			if (color <= 0)
				color = 0;
			draw->colors[end_y] = color;
		}
		end_y++;
	}
}

void	draw_scene(t_draw *draw, t_thread_params *params)
{
	float	step;
	int		start_y;
	int		end_y;

	draw->dist = lane_distance(draw);
	draw->height = (BLOCK_SIZE * HEIGHT) / draw->dist;
	draw->tex_y = get_check(&start_y, &end_y, &step, draw->height);
	draw_ceiling(draw, params, start_y);
	draw_wall(draw, start_y, end_y);
	draw_floor(draw, params, end_y);
}

void	draw_line(t_draw draw, t_thread_params *params)
{
	t_cube	*c;
	int		scale;
	int		iter;

	c = params->cube;
	draw.cosangle = cos(draw.angle);
	draw.sinangle = sin(draw.angle);
	iter = 0;
	while (!find_hitbox(&draw, c, &iter))
	{
		draw.x += draw.cosangle;
		draw.y += draw.sinangle;
	}
	direction(&draw, params);
	draw_sprite(&draw, params);
	draw_scene(&draw, params);
	scale = draw.start_x + get_quality(params->render);
	while (draw.start_x < scale && draw.start_x < params->end)
	{
		put_line(draw, params);
		draw.start_x++;
	}
}
