/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:49:03 by escura            #+#    #+#             */
/*   Updated: 2024/10/06 16:24:28 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_level_con(t_portal *portals, float px, float py, int i)
{
	float	y;
	float	x;

	x = 0;
	y = 0;
	while (portals[i].x != -1)
	{
		x = portals[i].x * BLOCK_SIZE;
		y = portals[i].y * BLOCK_SIZE;
		if (px >= x && px <= x + BLOCK_SIZE && py >= y && py <= y
			&& !portals[i].open)
			return (true);
		if (py < portals[i].y * BLOCK_SIZE + 10)
		{
			player()->level = (cube()->levels - 1) - i;
			break ;
		}
		else
			player()->level = 0;
		i++;
	}
	return (false);
}

static bool	check_level(t_portal *portals, float px, float py)
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
				|| touch_doors(c->map->doors, x, y)
				|| touch_generator(c->map->generators, x, y)
				|| check_level(c->map->portals, x, y))
				return (true);
			y++;
		}
		x++;
	}
	return (false);
}
