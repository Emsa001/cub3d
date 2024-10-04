/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_points.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:19:37 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/04 19:19:40 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_generator_first_coordinates(t_draw *draw, t_block *generators)
{
	int	sx;

	sx = -1;
	if (draw->cosangle > 0)
		sx = 1;
	draw->gen.x = draw->x;
	draw->gen.y = draw->y;
	draw->gen.dist = lane_distance(draw);
	draw->gen.height = (BLOCK_SIZE * HEIGHT) / draw->gen.dist;
	draw->gen.tex_x = (int)draw->y % BLOCK_SIZE;
	if (touch_generator(generators, draw->x - sx, draw->y))
		draw->gen.tex_x = (int)draw->x % BLOCK_SIZE;
	draw->gen.save = true;
}

void	get_generator_last_coordinates(t_draw *draw)
{
	(void)generators;
	draw->gen.dist = lane_distance(draw);
	draw->gen.height_top = (BLOCK_SIZE * HEIGHT) / draw->gen.dist;
	draw->gen.save = false;
}

int	touch_sprite(t_sprite *sprites, float px, float py)
{
	int		i;
	float	x;
	float	y;

	i = 0;
	x = 0;
	y = 0;
	if (!sprites)
		return (0);
	while (sprites[i].x != -1)
	{
		x = sprites[i].x * BLOCK_SIZE;
		y = sprites[i].y * BLOCK_SIZE;
		if (px >= x && px <= x + sprites[i].width && py >= y 
			&& py <= y + SPRITE_THICKNESS)
			return (i + 1);
		i++;
	}
	return (0);
}

int	touch_facing_sprite(t_draw *draw, t_sprite *sprites, float px, float py)
{
	int		i;
	t_float	p;
	t_float	s;

	p.x = px;
	p.y = py;
	i = 0;
	s.x = 0;
	s.y = 0;
	if (!sprites)
		return (0);
	while (sprites[i].x != -1)
	{
		s.x = sprites[i].x * BLOCK_SIZE;
		s.y = sprites[i].y * BLOCK_SIZE;
		if (touch_facing(draw, p, s, sprites[i].width))
			return (i + 1);
		i++;
	}
	return (0);
}

bool	find_hitbox(t_draw *draw, t_cube *c)
{
	int	i;

	i = 0;
	if (is_touching(draw->x, draw->y, c))
		return (true);
	if (touch_block(c->map->blocks, draw->x, draw->y))
		return (true);
	if (touch_block(c->map->doors, draw->x, draw->y))
		return (true);
	if (touch_line(c->map->lines, draw->x, draw->y))
		return (true);
	i = touch_sprite(c->map->sprites, draw->x, draw->y);
	if (i)
		get_sprite_coordinates(draw, i);
	i = touch_facing_sprite(draw, c->map->facing, draw->x, draw->y);
	if (i)
		get_facing_coordinates(draw, i);
	if (!draw->gen.save && touch_generator(c->map->generators, draw->x,
			draw->y))
		get_generator_first_coordinates(draw, c->map->generators);
	if (draw->gen.save && !touch_generator(c->map->generators, draw->x,
			draw->y))
		get_generator_last_coordinates(draw);
	return (false);
}
