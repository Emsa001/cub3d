/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:30:33 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 16:10:47 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool touch_edge(float x, float y, t_cube *c)
{
	if (x >= 0 && y >= 0 && x < c->map->width * BLOCK_SIZE && y < c->map->height * BLOCK_SIZE)
		return false;
	return true;
}

bool touch_block(t_block *blocks, float px, float py)
{
	int i = 0;
	float x, y;

	if (!blocks)
		return false;

	while (blocks[i].x != -1)
	{
		x = blocks[i].x * BLOCK_SIZE;
		y = blocks[i].y * BLOCK_SIZE;
		if (px >= x && px <= x + BLOCK_SIZE && py >= y && py <= y + BLOCK_SIZE)
			return true;
		i++;
	}
	return false;
}

bool is_touching(float px, float py, t_cube *c)
{
	int x = px / BLOCK_SIZE;
	int y = py / BLOCK_SIZE;

	if (x < 0 || y < 0 || x >= c->map->width || y >= c->map->height)
		return (true);
	if (c->map->map[y][x] == WALL)
		return (true);
	return (false);
}
