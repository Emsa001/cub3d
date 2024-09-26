/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:44 by escura            #+#    #+#             */
/*   Updated: 2024/09/25 17:12:57 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Distance calculation function
float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	lane_distance(t_draw *draw)
{
	const float	x2 = player()->x_px;
	const float	y2 = player()->y_px;
	const float	player_angle = player()->angle;
	float		raw_distance;
	float		adjusted_distance;

	raw_distance = distance(draw->first_x, draw->first_y, x2, y2);
	adjusted_distance = raw_distance * cos(player_angle - draw->angle);
	draw->generator_dist = adjusted_distance;
	draw->height_top = (BLOCK_SIZE * HEIGHT) / adjusted_distance;
	raw_distance = distance(draw->last_x, draw->last_y, x2, y2);
	adjusted_distance = raw_distance * cos(player_angle - draw->angle);
	draw->height = (BLOCK_SIZE * HEIGHT) / adjusted_distance;
	raw_distance = distance(draw->x, draw->y, x2, y2);
	adjusted_distance = raw_distance * cos(player_angle - draw->angle);
	draw->dist = adjusted_distance;
	draw->wall_height = (BLOCK_SIZE * HEIGHT) / adjusted_distance;
}

static void	init_cells(char *nearby_cells, int x, int y)
{
	const t_cube	*c = cube();

	nearby_cells[0] = c->map->map[y][x];
	nearby_cells[1] = c->map->map[y - 1][x];
	nearby_cells[2] = c->map->map[y + 1][x];
	nearby_cells[3] = c->map->map[y][x - 1];
	nearby_cells[4] = c->map->map[y][x + 1];
	nearby_cells[5] = c->map->map[y - 1][x - 1];
	nearby_cells[6] = c->map->map[y - 1][x + 1];
	nearby_cells[7] = c->map->map[y + 1][x - 1];
	nearby_cells[8] = c->map->map[y + 1][x + 1];
}

static t_location	*is_nearby1(int x, int y, int i)
{
	t_location	*loc;
	t_location	*offsets;

	offsets = (t_location[]){{0, 0}, {0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1},
	{1, -1}, {-1, 1}, {1, 1}};
	loc = ft_malloc(sizeof(t_location));
	loc->x = x + offsets[i].x;
	loc->y = y + offsets[i].y;
	return (loc);
}

t_location	*is_nearby(char cell)
{
	const t_player	*p = player();
	const int		x = (int)p->x_px / BLOCK_SIZE;
	const int		y = (int)p->y_px / BLOCK_SIZE;
	char			nearby_cells[9];
	int				i;

	init_cells(nearby_cells, x, y);
	i = 0;
	while (i < 9)
	{
		if (nearby_cells[i] == cell)
			return (is_nearby1(x, y, i));
		i++;
	}
	return (NULL);
}
