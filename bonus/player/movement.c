/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:53 by escura            #+#    #+#             */
/*   Updated: 2024/07/18 15:40:25 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (touch())
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

    if(p->spawn)
    {
        spawn_block(p->angle, 1);
        p->spawn = false;
    }
    if(p->remove)
    {
        spawn_block(p->angle, 0);
        p->remove = false;
    }
    if(p->catch)
        catch_block(p->angle);

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


bool	touch()
{
	const int	x = player()->x_px;
	const int	y = player()->y_px;
	const char	**map = cube()->map->map;

    const int x_p = x + 10;
    const int y_p = y + 10;
    const int x_m = x - 10;
    const int y_m = y - 10;
    char c = '1';
    char b = '2';
    char d = 'D';

    if(is_touching(x_m , y_m, c) || is_touching(x_p , y_m, c) || is_touching(x_m , y_p, c) || is_touching(x_p , y_p, c))
        return (true);
    if(touch_block(cube()->map->blocks, x_m, y_m, b) || touch_block(cube()->map->blocks, x_p, y_m, b) || touch_block(cube()->map->blocks, x_m, y_p, b) || touch_block(cube()->map->blocks, x_p, y_p, b))
        return (true);
    if(touch_block(cube()->map->doors, x_m, y_m, d) || touch_block(cube()->map->doors, x_p, y_m, d) || touch_block(cube()->map->doors, x_m, y_p, d) || touch_block(cube()->map->doors, x_p, y_p, d))
        return (true);

	return (false);
}
