/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:53 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 12:42:57 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void try_move(float x, float y)
{
	const t_cube *c = cube();
	t_player *p = player();

	int temp_x = p->x_px;
	int temp_y = p->y_px;

	p->x_px += x;
	p->y_px += y;

	if(touch(WALL)){
		p->x_px -= x;
		p->y_px -= y;
	}
}

int	movement(void)
{
	t_player *p = player();
	const t_cube *c = cube();

	// print_map_info();

	float cos_angle = cos(p->angle);
	float sin_angle = sin(p->angle);

	if(p->btn_w || p->btn_s)
	{
		if(p->btn_s)
		{
			cos_angle = -cos_angle;
			sin_angle = -sin_angle;
		}

		try_move(0, p->speed * sin_angle);
		try_move(p->speed * cos_angle,0);
	}

	if (p->btn_a)
	{
		p->angle -= 0.1;
		if (p->angle < 0)
			p->angle += 2 * PI;
	}
	if (p->btn_d)
	{
		p->angle += 0.1;
		if (p->angle > 2 * PI)
			p->angle -= 2 * PI;
	}

	p->x = p->x_px / BLOCK_SIZE;
	p->y = p->y_px / BLOCK_SIZE;

	p->x_dir = cos(p->angle) * 5;
	p->y_dir = sin(p->angle) * 5;

	return (0);
}

bool touch(char c)
{
    const int x = player()->x_px / BLOCK_SIZE;
    const int y = player()->y_px / BLOCK_SIZE;
    const char **map = cube()->map->map;
    
    return map[y][x] && map[y][x] == c;
}