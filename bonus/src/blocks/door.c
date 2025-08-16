/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42wolfsburg.de>     +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:41 by btvildia          #+#    #+#             */
/*   Updated: 2024/07/21 13:14:12 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	opening_door(t_map *map, int id, int side)
{
	float	move_step;

	move_step = 0.05;
	if (side == 1 && map->doors[id].x >= map->doors[id].s_x - 0.9)
		map->doors[id].x -= move_step;
	else if (side == 2 && map->doors[id].y >= map->doors[id].s_y - 0.9)
		map->doors[id].y -= move_step;
	else if (side == 3 && map->doors[id].x <= map->doors[id].s_x + 0.9)
		map->doors[id].x += move_step;
	else if (side == 4 && map->doors[id].y <= map->doors[id].s_y + 0.9)
		map->doors[id].y += move_step;
}

void	closing_door(t_map *map, int id, int side)
{
	float	move_step;

	move_step = 0.05;
	if (side == 1 && map->doors[id].x <= map->doors[id].s_x)
		map->doors[id].x += move_step;
	else if (side == 2 && map->doors[id].y <= map->doors[id].s_y)
		map->doors[id].y += move_step;
	else if (side == 3 && map->doors[id].x >= map->doors[id].s_x)
		map->doors[id].x -= move_step;
	else if (side == 4 && map->doors[id].y >= map->doors[id].s_y)
		map->doors[id].y -= move_step;
}

bool	check_door_opened(t_map *map, int id, int side)
{
	if ((side == 1 && map->doors[id].x <= map->doors[id].s_x - 0.9)
		|| (side == 2 && map->doors[id].y <= map->doors[id].s_y - 0.9)
		|| (side == 3 && map->doors[id].x >= map->doors[id].s_x + 0.9)
		|| (side == 4 && map->doors[id].y >= map->doors[id].s_y + 0.9))
		return (true);
	return (false);
}

bool	check_door_closed(t_map *map, int id, int side)
{
	if ((side == 1 && map->doors[id].x >= map->doors[id].s_x) || (side == 2
			&& map->doors[id].y >= map->doors[id].s_y) || (side == 3
			&& map->doors[id].x <= map->doors[id].s_x) || (side == 4
			&& map->doors[id].y <= map->doors[id].s_y))
		return (true);
	return (false);
}

void	move_door(t_map *map, t_player *p, bool opening)
{
	int	side;
	int	id;

	side = 0;
	id = get_block_id(map->doors, p->x, p->y, p->angle);
	if (id == -1)
		return ;
	side = get_side(map->doors[id].s_x, map->doors[id].s_y, map->map);
	if (!side)
		return ;
	if (opening)
	{
		opening_door(map, id, side);
		if (check_door_opened(map, id, side))
			p->opened = true;
	}
	else
	{
		closing_door(map, id, side);
		if (check_door_closed(map, id, side))
			p->opened = false;
	}
	if (p->opened == opening)
		p->interact = false;
}
