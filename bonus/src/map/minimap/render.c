/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:16:56 by escura            #+#    #+#             */
/*   Updated: 2024/09/28 20:32:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_coords(float *bx, float *by, float angle)
{
	float	old_bx;
	float	old_by;

	old_bx = *bx;
	old_by = *by;
	*bx = old_bx * cos(angle) - old_by * sin(angle);
	*by = old_bx * sin(angle) + old_by * cos(angle);
}

void	draw_blocks(t_minimap *m, t_map *map, t_player *p)
{
	int		x;
	int		y;
	int		bx;
	int		by;
	float	rel_x;
	float	rel_y;
	float	angle;

	x = 0;
	y = 0;
	bx = 0;
	by = 0;
	rel_x = 0;
	rel_y = 0;
	angle = p->angle;
	while (map->map[y] != NULL)
	{
		while (map->map[y][x] != '\0')
		{
			if (map->map[y][x] == '1' || map->map[y][x] == 'D' || map->map[y][x] == 'M' || map->map[y][x] == 'G' || map->map[y][x] == 'P')
			{
				rel_x = (x - p->x) * SQUARE_SIZE + SQUARE_SIZE / 2;
				rel_y = (y - p->y) * SQUARE_SIZE + SQUARE_SIZE / 2;
				rotate_coords(&rel_x, &rel_y, -(angle + PI / 2));
				bx = m->center_x - SQUARE_SIZE / 2 + rel_x;
				by = m->center_y - SQUARE_SIZE / 2 + rel_y;
				draw_block(bx, by, -(angle + PI / 2), map->map[y][x]);
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	render_minimap(void)
{
	t_minimap *m = minimap();
	t_map *map = cube()->map;
	t_player *p = player();

	draw_minimap_square(m->x, m->y);
	draw_player(m->center_x, m->center_y);

	draw_blocks(m, map, p);
}