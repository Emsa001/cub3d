/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:59:22 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/05 15:06:53 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	view_current_distance_gen(int start_y, float angle, float z)
{
	float	current_dist;
	float	view;

	current_dist = (player()->z - z) * HEIGHT / (start_y - HEIGHT / 2);
	view = current_dist / cos(angle - player()->angle);
	return (view);
}

void	draw_generator_top(t_draw *draw, t_thread_params *params, int start_y,
		int end_y)
{
	const t_player	*p = params->player;
	int				color;
	float			head_x;
	float			head_y;
	float			current_dist;

	if (current_frame(2) == 1)
		draw->gen.top += 0.01;
	while (start_y < end_y)
	{
		if (draw->colors[start_y] == 0)
		{
			current_dist = view_current_distance_gen(start_y, draw->angle,
					draw->gen.top);
			head_x = (p->x) + current_dist * draw->cosangle;
			head_y = (p->y) + current_dist * draw->sinangle;
			color = get_pixel_from_image(params->textures->generator_top, head_x
					* (T_SIZE * 2), head_y * (T_SIZE * 2));
			color = darken_color(color, current_dist / 7);
			if (color > 0)
				draw->colors[start_y] = color;
		}
		start_y++;
	}
}

void	check_line(t_line *line)
{
	if (line->start_y < 0)
	{
		line->tex_y = -line->start_y * line->step;
		line->start_y = 0;
	}
	if (line->end_y > HEIGHT)
		line->end_y = HEIGHT;
}

void	draw_generator(t_draw *draw, t_thread_params *params, int height,
		int tex_x)
{
	t_line		line;
	t_texture	*tex;

	line.start_y = (player()->z - draw->gen.tall) * height + HEIGHT / 2;
	line.end_y = line.start_y + height * draw->gen.tall;
	line.tex_y = 0;
	line.step = (float)(T_SIZE * 1.5) / height;
	tex = params->textures->generator[current_frame(2)];
	check_line(&line);
	while (line.start_y < line.end_y)
	{
		if (draw->colors[line.start_y] == 0)
		{
			line.color = get_pixel_from_image(tex, tex_x * 2, line.tex_y);
			line.color = darken_color(line.color, (float)draw->gen.dist / 450);
			if (line.color > 0)
				draw->colors[line.start_y] = line.color;
		}
		line.tex_y += line.step;
		line.start_y++;
	}
}

void	draw_generators(t_draw *draw, t_thread_params *params)
{
	int	start_y;
	int	end_y;

	(void)params;
	start_y = HEIGHT / 2 + ((player()->z - draw->gen.top)
			* draw->gen.height_top);
	end_y = HEIGHT / 2 + ((player()->z - draw->gen.top) * draw->gen.height);
	if (start_y < 0)
		start_y = 0;
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	draw_generator(draw, params, draw->gen.height, draw->gen.tex_x);
	draw_generator_top(draw, params, start_y, end_y);
}
