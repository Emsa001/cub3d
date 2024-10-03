/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_points.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:19:37 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/03 14:20:41 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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

bool	touch_facing(t_draw *draw, float px, float py, float sprite_x,
		float sprite_y, int width)
{
	float	cosangle;
	float	sinangle;
	float	u;
	float	v;
	float	dist;

	// it's the same as cos(angle + 90)
	cosangle = cos(player()->angle);
	// it's the same as sin(angle + 90)
	sinangle = sin(player()->angle);
	u = (cosangle * (sprite_x - px) + sinangle * (sprite_y - py));
	if (u < 0 || u > 2)
		return (false);
	v = (-sinangle * (sprite_x - px) + cosangle * (sprite_y - py));
	draw->facing[draw->f_count].tex_x = (int)v + width / 2;
	dist = distance(px, py, sprite_x, sprite_y);
	if (dist * 2 < width)
		return (true);
	return (false);
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
		if (px >= x && px <= x + sprites[i].width && py >= y && py <= y + 1)
			return (i + 1);
		i++;
	}
	return (0);
}
int	touch_facing_sprite(t_draw *draw, t_sprite *sprites, float px, float py)
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
		if (touch_facing(draw, px, py, x, y, sprites[i].width))
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
	if ((i = touch_sprite(c->map->sprites, draw->x, draw->y)))
		get_sprite_coordinates(draw, i);
	if ((i = touch_facing_sprite(draw, c->map->facing, draw->x, draw->y)))
		get_facing_coordinates(draw, i);
	return (false);
}

