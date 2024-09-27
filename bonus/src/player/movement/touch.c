/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:49:03 by escura            #+#    #+#             */
/*   Updated: 2024/09/27 20:24:15 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_level_con(t_point *portals, float px, float py, int i)
{
	const t_sprite	*sprites = cube()->map->sprites;
	float			y;
	float			x;

	x = 0;
	y = 0;
	while (portals[i].x != -1)
	{
		x = portals[i].x * BLOCK_SIZE;
		y = portals[i].y * BLOCK_SIZE;
		if (px >= x && px <= x + BLOCK_SIZE && py >= y && py <= y
			&& sprites[i].type == 'P')
			return (true);
		if (py < portals[i].y * BLOCK_SIZE + 10)
		{
			player()->level = 2 - i;
			break ;
		}
		else
			player()->level = 0;
		i++;
	}
	return (false);
}

bool	check_level(t_point *portals, float px, float py)
{
	int	i;

	i = 0;
	if (!portals)
		return (false);
	return (check_level_con(portals, px, py, i));
}

bool	touch(void)
{
	const t_cube	*c = cube();
	int				x;
	int				y;

	x = player()->x_px - 10;
	y = player()->y_px - 10;
	while (x <= player()->x_px + 10)
	{
		y = player()->y_px - 10;
		while (y <= player()->y_px + 10)
		{
			if (is_touching(x, y, c) || touch_block(c->map->blocks, x, y)
				|| touch_block(c->map->doors, x, y)
				|| touch_generator(c->map->generators, x, y)
				|| touch_line(c->map->lines, x, y)
				|| check_level(c->map->portals, x, y))
				return (true);
			y++;
		}
		x++;
	}
	return (false);
}
