/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:47:24 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/12 14:29:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	view_current_distance_gen(const t_player *p, int start_y, float angle,
		float z)
{
	float	current_dist;

	current_dist = (p->z - z) * HEIGHT / (start_y - HEIGHT / 2);
	return (current_dist / cos(angle - p->angle));
}

void	draw_generator(t_draw *draw, t_thread_params *params, int tex_x,
		float angle)
{
	int				color;
	float			tex_y;
	int				dist;
	float			step;
	const t_player	*p = params->player;
	t_render		*r;
	int				start_y;
	int				end_y;
	t_texture		*generator_animation[2] = {params->textures->generator,
				params->textures->generator1};
	t_texture		*generator;

	color = params->color;
	tex_y = 0;
	dist = draw->generator_dist;
	step = (float)(T_SIZE * 1.5) / draw->height_top;
	r = params->render;
	start_y = (p->z - 0.6) * draw->height_top + vert_offset(p);
	end_y = start_y + draw->height_top * 0.6;
	generator = generator_animation[current_frame(2)];
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	while (start_y < end_y)
	{
		color = get_pixel_from_image(generator, tex_x * 2, tex_y);
		color = darken_color(color, (float)dist / 450);
		if (color > 0)
			draw->colors[start_y] = color;
		tex_y += step;
		start_y++;
	}
}

void	draw_generator_top(t_draw *draw, t_thread_params *params, float angle)
{
	const t_cube		*c = params->cube;
	const t_player		*p = params->player;
	const t_textures	*texs = params->textures;
	float				head_x;
	float				head_y;
	float				cosangle;
	float				sinangle;
	float				tallness;
	int					color;
	int					start_y;
	int					end_y;
	float				current_dist;
	t_texture			*head;

	head_x = 0;
	head_y = 0;
	cosangle = cos(angle);
	sinangle = sin(angle);
	tallness = 0.49;
	if (current_frame(2) == 0)
		tallness = 0.48;
	color = 123;
	start_y = HEIGHT / 2 + ((p->z - tallness) * draw->height);
	end_y = (HEIGHT / 2 + ((p->z - tallness) * draw->height_top))
		+ draw->height_top * 0.01;
	current_dist = 0;
	head = texs->wall_south[p->level];
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	while (start_y < end_y)
	{
		current_dist = view_current_distance_gen(p, start_y, angle, tallness);
		color = get_pixel_from_image(params->textures->generator_top, head_x
				* (T_SIZE * 2), head_y * (T_SIZE * 2));
		color = darken_color_wall(color, (float)current_dist / 7, head_x,
				head_y);
		head_x = (p->x) + current_dist * cosangle;
		head_y = (p->y) + current_dist * sinangle;
		if (color > 0)
			draw->colors[start_y] = color;
		start_y++;
	}
}
// void	draw_line(t_draw draw, t_thread_params *params)
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


// int	generator_direction(t_draw *draw, float cosangle, float sinangle, t_cube *c)
// {
// 	int	sx;
// 	int	sy;

// 	sx = 0;
// 	sy = 0;
// 	if (cosangle > 0)
// 		sx = 1;
// 	else
// 		sx = -1;
// 	if (sinangle > 0)
// 		sy = 1;
// 	else
// 		sy = -1;
// 	if (touch_generator(c->map->generators, draw->first_x - sx, draw->first_y))
// 	{
// 		draw->tex_x = (int)draw->first_x % BLOCK_SIZE;
// 		return (7);
// 	}
// 	else if (touch_generator(c->map->generators, draw->first_x, draw->first_y))
// 	{
// 		draw->tex_x = (int)draw->first_y % BLOCK_SIZE;
// 		return (7);
// 	}
// 	return (0);
// }
