/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:44 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 18:39:57 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Distance calculation function
float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	lane_distance(t_draw *draw)
{
	const float	player_angle = player()->angle;
	const float	x2 = player()->x_px;
	const float	y2 = player()->y_px;
	float		raw_distance;
	float		adjusted_distance;

	raw_distance = distance(draw->x, draw->y, x2, y2);
	adjusted_distance = raw_distance * cos(player_angle - draw->angle);
	return (adjusted_distance);
}

static void	init_cells(t_cube *c, char *nearby_cells, int x, int y)
{
	const int	dx[] = {0, 0, -1, 1, -1, -1, 1, 1};
	const int	dy[] = {0, -1, 0, 0, -1, 1, -1, 1};
	int			i;
	int			nx;
	int			ny;

	i = 0;
	while (i < 8)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx >= 0 && nx < c->map->width && ny >= 0 && ny < c->map->height)
			nearby_cells[i + 1] = c->map->map[ny][nx];
		else
			nearby_cells[i + 1] = '1';
		i++;
	}
	nearby_cells[0] = c->map->map[y][x];
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

	init_cells(cube(), nearby_cells, x, y);
	i = 0;
	while (i < 9)
	{
		if (nearby_cells[i] == cell)
			return (is_nearby1(x, y, i));
		i++;
	}
	return (NULL);
}
