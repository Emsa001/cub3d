/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:46:10 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/04 21:51:22 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch_facing(t_draw *draw, t_float p, t_float s, int width)
{
	float	cosangle;
	float	sinangle;
	float	u;
	float	v;
	float	dist;

	cosangle = cos(player()->angle);
	sinangle = sin(player()->angle);
	u = (cosangle * (s.x - p.x) + sinangle * (s.y - p.y));
	if (u < 0 || u > 2)
		return (false);
	v = (-sinangle * (s.x - p.x) + cosangle * (s.y - p.y));
	draw->facing[draw->f_count].tex_x = (int)v + width / 2;
	dist = distance(p.x, p.y, s.x, s.y);
	if (dist * 2 < width)
		return (true);
	return (false);
}

void	get_sprite_coordinates(t_draw *draw, int i, int *iter)
{
	int	it;

	i = i - 1;
	it = draw->s_count;
	draw->sprites[it].x = draw->x;
	draw->sprites[it].y = draw->y;
	draw->sprites[it].dist = lane_distance(draw);
	draw->sprites[it].height = (BLOCK_SIZE * HEIGHT) / draw->sprites[it].dist;
	draw->sprites[it].tex_x = (int)draw->x % BLOCK_SIZE;
	draw->sprites[it].sprite_tex = cube()->map->sprites[i].sprite_tex;
	draw->sprites[it].frames = cube()->map->sprites[i].frames;
	draw->s_count++;
	draw->is_sprite = true;
	draw->sprite_order[*iter] = 1;
	(*iter)++;
}

void	get_facing_coordinates(t_draw *draw, int i, int *iter)
{
	int	it;

	i = i - 1;
	it = draw->f_count;
	draw->facing[it].x = draw->x;
	draw->facing[it].y = draw->y;
	draw->facing[it].dist = lane_distance(draw);
	draw->facing[it].height = (BLOCK_SIZE * HEIGHT) / draw->facing[it].dist;
	draw->facing[it].sprite_tex = cube()->map->facing[i].sprite_tex;
	draw->facing[it].frames = cube()->map->facing[i].frames;
	draw->f_count++;
	draw->is_facing = true;
	draw->sprite_order[*iter] = 2;
	(*iter)++;
}

static void	draw_sprites(t_draw *draw, t_sprite_coords sprites)
{
	t_texture	*tex;
	t_line		line;

	tex = sprites.sprite_tex[current_frame(sprites.frames)];
	line.tex_y = get_check(&line.start_y, &line.end_y, &line.step,
			sprites.height);
	while (line.start_y < line.end_y)
	{
		if (draw->colors[line.start_y] == 0)
		{
			line.color = get_pixel_from_image(tex, sprites.tex_x, line.tex_y);
			line.color = darken_color_wall(line.color, (float)sprites.dist
					/ 450, sprites.x / BLOCK_SIZE, sprites.y / BLOCK_SIZE);
			if (line.color && line.color > 0)
				draw->colors[line.start_y] = line.color;
		}
		line.tex_y += line.step;
		line.start_y++;
	}
}

void	draw_sprite(t_draw *draw, t_thread_params *params)
{
	int	i;
	int	max_count;
	int	*order;

	i = 0;
	max_count = draw->s_count + draw->f_count + 1;
	order = draw->sprite_order;
	while (order[i] && i < max_count)
	{
		if (order[i] == 1 && i < draw->s_count)
			draw_sprites(draw, draw->sprites[i]);
		if (order[i] == 2 && i < draw->f_count)
			draw_sprites(draw, draw->facing[i]);
		if (order[i] == 3)
			draw_generators(draw, params);
		i++;
	}
}
