/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:46:57 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 15:40:16 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch_block(t_block *blocks, float px, float py)
{
	int		i;
	float	x;
	float	y;

	i = 0;
	if (!blocks)
		return (false);
	while (blocks[i].x != -1)
	{
		x = blocks[i].x * BLOCK_SIZE;
		y = blocks[i].y * BLOCK_SIZE;
		if (px >= x && px <= x + BLOCK_SIZE && py >= y && py <= y + BLOCK_SIZE)
			return (true);
		i++;
	}
	return (false);
}

int	touch_line(t_block *lines, float px, float py)
{
	int		i;
	float	x;
	float	y;

	if (!lines)
		return (false);
	i = 0;
	while (lines[i].x != -1)
	{
		x = lines[i].x * BLOCK_SIZE - L_WIDTH;
		y = lines[i].y * BLOCK_SIZE - L_WIDTH;
		if (px >= x && px <= x + (L_WIDTH * 2) && py >= y && py <= y + (L_WIDTH
				* 2))
			return (2);
		x = lines[i].s_x * BLOCK_SIZE - L_WIDTH;
		y = lines[i].s_y * BLOCK_SIZE - L_WIDTH;
		if (px >= x && px <= x + (L_WIDTH * 2) && py >= y && py <= y + (L_WIDTH
				* 2))
			return (2);
		if (check_if_point_is_on_line(lines[i], px, py))
			return (1);
		i++;
	}
	return (0);
}

bool	touch_generator(t_block *gens, float px, float py)
{
	int		i;
	float	x;
	float	y;

	i = 0;
	if (!gens)
		return (false);
	while (gens[i].x != -1)
	{
		x = gens[i].x * BLOCK_SIZE;
		y = gens[i].y * BLOCK_SIZE;
		if (px >= x && px <= x + BLOCK_SIZE / 2 && py >= y && py <= y
			+ BLOCK_SIZE / 2)
			return (true);
		i++;
	}
	return (false);
}

bool	is_touching(float px, float py, const t_cube *c)
{
	const int	x = px / BLOCK_SIZE;
	const int	y = py / BLOCK_SIZE;

	if (x < 0 || y < 0 || x >= c->map->width || y >= c->map->height)
		return (true);
	if (c->map->map[y][x] == WALL)
		return (true);
	return (false);
}