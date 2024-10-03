/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:46:18 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 14:35:20 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_draw *draw, t_thread_params *params, int start_y)
{
	float		current_dist;
	t_texture	*tex;
	int			color;

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

void	draw_wall(t_draw *draw, t_thread_params *params, int start_y, int end_y)
{
	int		color;
	float	step;

	step = ((float)T_SIZE) / draw->wall_height;
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

	draw->tex_y = get_check(&start_y, &end_y, &step, draw->wall_height);
	// draw ceiling
	draw_ceiling(draw, params, start_y);
	// draw wall
	draw_wall(draw, params, start_y, end_y);
	// draw floor
	draw_floor(draw, params, end_y);
}

void	draw_line(t_draw draw, t_thread_params *params)
{
	t_cube	*c;
	int		scale;

	c = params->cube;
	draw.cosangle = cos(draw.angle);
	draw.sinangle = sin(draw.angle);
	while (!find_hitbox(&draw, c))
	{
		draw.x += draw.cosangle;
		draw.y += draw.sinangle;
	}
	direction(&draw, params);
	draw.dist = lane_distance(&draw);
	draw.wall_height = (BLOCK_SIZE * HEIGHT) / draw.dist;
	draw_sprite(&draw, params);
	draw_scene(&draw, params);
	scale = draw.start_x + WIDTH_SCALE;
	while (draw.start_x < scale && draw.start_x < params->end)
	{
		put_line(draw, params);
		draw.start_x++;
	}
}

// void	draw_line_old(t_draw draw, t_thread_params *params)
// {
// 	t_cube *c = params->cube;
// 	const t_player *p = params->player;
// 	float cosangle = cos(draw.angle);
// 	float sinangle = sin(draw.angle);

// 	bool save = false;
// 	bool save_last = false;

// 	t_float *touch = malloc(sizeof(t_float) * c->map->sprite_count);
// 	ft_bzero(touch, sizeof(t_float) * c->map->sprite_count);
// 	int i = 0;

// 	while (!find_hitbox(draw.x, draw.y, c))
// 	{
// 		if (touch_sprite(c->map->sprites, draw.x, draw.y)
// 			|| touch_facing_sprite(&draw, c->map->facing, draw.x, draw.y))
// 		{
// 			touch[i].x = draw.x;
// 			touch[i].y = draw.y;
// 			i++;
// 		}
// 		if (touch_generator(c->map->generators, draw.x, draw.y))
// 		{
// 			if (!save)
// 			{
// 				save = true;
// 				draw.first_x = draw.x;
// 				draw.first_y = draw.y;
// 			}
// 			draw.x += cosangle;
// 			draw.y += sinangle;
// 			if (!save_last && !touch_generator(c->map->generators, draw.x,
// 					draw.y))
// 			{
// 				save_last = true;
// 				draw.last_x = draw.x;
// 				draw.last_y = draw.y;
// 			}
// 		}
// 		else
// 		{
// 			draw.x += cosangle;
// 			draw.y += sinangle;
// 		}
// 	}

// 	draw.side = direction(draw.x, draw.y, cosangle, sinangle, c, &draw.tex_x);
// 	lane_distance(&draw);
// 	draw_scene(&draw, params);
// 	while (i > 0)
// 	{
// 		draw.sprite_x = touch[i].x;
// 		draw.sprite_y = touch[i].y;
// 		sprite_dist(&draw);
// 		int j = 0;
// 		if ((j = touch_sprite(c->map->sprites, draw.sprite_x, draw.sprite_y)))
// 		{
// 			draw.tex_x = (int)draw.sprite_x % BLOCK_SIZE;
// 			sprite_frame(&draw, params, c->map->sprites[j - 1]);
// 		}
// 		else if (touch_facing_sprite(&draw, c->map->facing, draw.sprite_x,
// 				draw.sprite_y))
// 			sprite_frame(&draw, params, c->map->facing[0]);
// 		i--;
// 	}
// 	if (generator_direction(&draw, cosangle, sinangle, c) == 7)
// 	{
// 		draw_generator_top(&draw, params, draw.angle);
// 		draw_generator(&draw, params, draw.tex_x, draw.angle);
// 	}
// 	int scale = draw.start_x + WIDTH_SCALE;
// 	while (draw.start_x < scale && draw.start_x < params->end)
// 	{
// 		put_line(draw, params);
// 		draw.start_x++;
// 	}
// 	free(touch);
// }