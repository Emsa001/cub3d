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

void	draw_generator(t_draw *draw, ThreadParams *params, int tex_x,
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

void	draw_generator_top(t_draw *draw, ThreadParams *params, float angle)
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
