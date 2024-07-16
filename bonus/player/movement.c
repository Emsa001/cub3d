/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:53 by escura            #+#    #+#             */
/*   Updated: 2024/07/16 21:18:56 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void open_door(void)
{
    t_player *p = player();
    t_cube *c = cube();
    t_door *doors = c->map->doors;
    static int open;
    
    if(doors[0].y >= doors[0].first_y - 0.8 && doors[0].y == doors[0].first_y)
            open = 1;
    else if(doors[0].y <= doors[0].first_y && doors[0].y <= doors[0].first_y - 0.8)
            open = 0;

    if(open == 1)
        doors[0].y = doors[0].y - 0.05;
    else
        doors[0].y = doors[0].y + 0.05;

    p->interact = false;
}

void	try_move(float x, float y)
{
	const t_cube	*c = cube();
	t_player		*p;
	int				temp_x;
	int				temp_y;

	p = player();
	temp_x = p->x_px;
	temp_y = p->y_px;
	p->x_px += x;
	p->y_px += y;
	if (touch(WALL))
	{
		p->x_px -= x;
		p->y_px -= y;
	}
}

void move_player(void) {
    t_player *p = player();
    float cos_angle = cos(p->angle);
    float sin_angle = sin(p->angle);
    float left_angle, right_angle;

    if (p->btn_w || p->btn_s) {
        if (p->btn_s) {
            cos_angle = -cos_angle;
            sin_angle = -sin_angle;
        }
        try_move(0, p->speed * sin_angle);
        try_move(p->speed * cos_angle, 0);
    }
    if (p->btn_a) {
        left_angle = p->angle - PI / 2;
        try_move(0, p->speed * sin(left_angle));
        try_move(p->speed * cos(left_angle), 0);
    }
    if (p->btn_d) {
        right_angle = p->angle + PI / 2;
        try_move(0, p->speed * sin(right_angle));
        try_move(p->speed * cos(right_angle), 0);
    }
    if (p->btn_left) {
        p->angle -= 0.1;
        if (p->angle < 0)
            p->angle += 2 * PI;
    }
    if (p->btn_right) {
        p->angle += 0.1;
        if (p->angle > 2 * PI)
            p->angle -= 2 * PI;
    }

    if(p->btn_up)
    {
        p->z_dir += 0.1;
        if(p->z_dir > 2)
            p->z_dir = 2;
    }
    if(p->btn_down)
    {
        p->z_dir -= 0.1;
        if(p->z_dir < -2)
            p->z_dir = -2;
    }

    if(p->interact)
        open_door();

    p->x = p->x_px / BLOCK_SIZE;
    p->y = p->y_px / BLOCK_SIZE;

    // Update direction vectors based on angle
    p->x_dir = cos(p->angle);
    p->y_dir = sin(p->angle);

    p->direction = p->angle * (180 / PI);
    if (p->direction > 180)
        p->direction -= 360;
    
    // printf("\n");
    // printf("direction: %f\n", p->direction);
    // printf("angle: %f\n", p->angle);
    // printf("x_dir: %f\n", p->x_dir);
    // printf("y_dir: %f\n", p->y_dir);
    // printf("x: %f\n", p->x);
    // printf("y: %f\n", p->y);
    // printf("\n");

    // float tmp_x = p->plane_x;
    // p->plane_x = p->plane_x * cos(p->speed) - p->plane_y * sin(p->speed);
	// p->plane_y = tmp_x * sin(p->speed) + p->plane_y * cos(p->speed);
}


bool	touch(char c)
{
	const int	x = player()->x_px;
	const int	y = player()->y_px;
	const char	**map = cube()->map->map;

    if(is_touching(x - 10, y - 10, c) || is_touching(x + 10, y - 10, c) || is_touching(x - 10, y + 10, c) || is_touching(x + 10, y + 10, c))
        return (true);
    if(touch_door(x - 10, y - 10) || touch_door(x + 10, y - 10) || touch_door(x - 10, y + 10) || touch_door(x + 10, y + 10)) 
        return (true);
    
	return (false);
}
