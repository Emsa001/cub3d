/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:53 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 13:57:04 by escura           ###   ########.fr       */
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

void	move_player(void)
{
	t_player *p = player();
	const t_cube *c = cube();

	print_map_info();

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
		try_move(p->speed * cos_angle, 0);
	}
	
    if (p->btn_a)
    {
        float left_angle = p->angle - PI / 2;
        try_move(p->speed * cos(left_angle), p->speed * sin(left_angle));
    }

    if (p->btn_d)
    {
        float right_angle = p->angle + PI / 2;
        try_move(p->speed * cos(right_angle), p->speed * sin(right_angle));
    }

	if(p->btn_left)
	{
		p->angle -= 0.1;
		if (p->angle < 0)
			p->angle += 2 * PI;
	}
	if(p->btn_right)
	{
		p->angle += 0.1;
		if (p->angle > 2 * PI)
			p->angle -= 2 * PI;
	}

	p->x = p->x_px / BLOCK_SIZE;
	p->y = p->y_px / BLOCK_SIZE;
}

bool touch(char c)
{
    const int x = player()->x_px / BLOCK_SIZE;
    const int y = player()->y_px / BLOCK_SIZE;
    const char **map = cube()->map->map;
    
	return is_touching(x, y, c);
}