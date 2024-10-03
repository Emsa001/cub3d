/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:46:10 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/03 18:44:54 by btvildia         ###   ########.fr       */
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

void	get_sprite_coordinates(t_draw *draw, int i)
{
	int	iter;

	i = i - 1;
	iter = draw->s_count;
	draw->sprites[iter].x = draw->x;
	draw->sprites[iter].y = draw->y;
	draw->sprites[iter].dist = lane_distance(draw);
	draw->sprites[iter].height = (BLOCK_SIZE * HEIGHT)
		/ draw->sprites[iter].dist;
	draw->sprites[iter].tex_x = (int)draw->x % BLOCK_SIZE;
	draw->sprites[iter].sprite_tex = cube()->map->sprites[i].sprite_tex;
	draw->sprites[iter].frames = cube()->map->sprites[i].frames;
	draw->s_count++;
	draw->is_sprite = true;
}

void	get_facing_coordinates(t_draw *draw, int i)
{
	int	iter;

	i = i - 1;
	iter = draw->f_count;
	draw->facing[iter].x = draw->x;
	draw->facing[iter].y = draw->y;
	draw->facing[iter].dist = lane_distance(draw);
	draw->facing[iter].height = (BLOCK_SIZE * HEIGHT) / draw->facing[iter].dist;
	draw->facing[iter].sprite_tex = cube()->map->facing[i].sprite_tex;
	draw->facing[iter].frames = cube()->map->facing[i].frames;
	draw->f_count++;
	draw->is_facing = true;
}

void	draw_sprites(t_draw *draw, t_thread_params *params,
		t_sprite_coords sprites)
{
	t_texture	*tex;
	t_line		line;

	tex = sprites.sprite_tex[current_frame(sprites.frames)];
	line.tex_y = get_check(&line.start_y, &line.end_y, &line.step,
			sprites.height);
	while (line.start_y < line.end_y)
	{
		line.color = get_pixel_from_image(tex, sprites.tex_x, line.tex_y);
		line.color = darken_color_wall(line.color, (float)sprites.dist / 450,
				sprites.x / BLOCK_SIZE, sprites.y / BLOCK_SIZE);
		if (line.color && line.color > 0)
			draw->colors[line.start_y] = line.color;
		line.tex_y += line.step;
		line.start_y++;
	}
}

void	draw_sprite(t_draw *draw, t_thread_params *params)
{
	if (draw->is_sprite)
		while (--draw->s_count >= 0)
			draw_sprites(draw, params, draw->sprites[draw->s_count]);
	if (draw->is_facing)
		while (--draw->f_count >= 0)
			draw_sprites(draw, params, draw->facing[draw->f_count]);
}
