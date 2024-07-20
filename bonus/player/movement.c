/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:53 by escura            #+#    #+#             */
/*   Updated: 2024/07/20 16:43:43 by btvildia         ###   ########.fr       */
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

float calculate_jump_speed(float z)
{
    if(z < -0.4)
        return 0.15;
    else if(z < -0.3)
        return 0.13;
    else if(z < -0.2)
        return 0.1;
    else if(z < -0.1)
        return 0.08;
    else
        return 0.05;
}

float calculate_fall_speed(float z)
{
    if(z < -0.4)
        return 0.15;
    else if(z < -0.3)
        return 0.13;
    else if(z < -0.2)
        return 0.1;
    else if(z < -0.1)
        return 0.08;
    else
        return 0.05;
}

void fall_player(void)
{
    t_player *p = player();
    if(p->z > -0.5)
        p->z -= calculate_fall_speed(p->z);
    else
        p->falling = false;
}

void jump_player(void)
{
    t_player *p = player();
    if(p->z < 0.1)
        p->z += calculate_jump_speed(p->z);
    else
    {
        p->jumping = false;
        p->falling = true;
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
        p->z += 0.1;
    if(p->btn_down)
        p->z -= 0.1;


    if(p->interact)
    {
        int id = get_block_id(cube()->map->doors, p->x, p->y, p->angle);
        if(p->opened)
            close_door(p->angle, id);
        else
            open_door(p->angle, id);
    }
    if(p->spawn)
    {
        add_block(p->angle);
        p->spawn = false;
    }
    if(p->remove)
    {
        remove_block(p->angle);
        p->remove = false;
    }
    if(p->catch)
        catch_block(p->angle);
    
    if(p->jump && !p->falling)
        p->jumping = true;
    if(p->jumping)
        jump_player();
    if(p->falling)
        fall_player();

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
    t_cube *c = cube();

    if(is_touching(x_m , y_m) || is_touching(x_p , y_m) || is_touching(x_m , y_p) || is_touching(x_p , y_p))
        return (true);
    if(touch_block(c->map->blocks, x_m, y_m) || touch_block(c->map->blocks, x_p, y_m) || touch_block(c->map->blocks, x_m, y_p) || touch_block(c->map->blocks, x_p, y_p))
        return (true);
    if(touch_block(c->map->doors, x_m, y_m) || touch_block(c->map->doors, x_p, y_m) || touch_block(c->map->doors, x_m, y_p) || touch_block(c->map->doors, x_p, y_p))
        return (true);

	return (false);
}
