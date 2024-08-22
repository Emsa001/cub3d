/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:46:56 by escura            #+#    #+#             */
/*   Updated: 2024/08/22 11:44:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void pouse_game(void)
{
    t_render *r = render();
    t_cube *c = cube();
    
    r->img_ptr = mlx_new_image(r->mlx, WIDTH, HEIGHT);
    
    mlx_put_image_to_window(r->mlx, r->win, r->img_ptr , 0, 0);
    mlx_destroy_image(r->mlx, r->img_ptr);
    
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

    static float step_progress = 0;
    float step_amplitude = 0.05;
    float step_frequency = 0.2;
    float base_z = 0.55;

    bool is_moving = false;

    if (p->btn_w || p->btn_s) {
        if (p->btn_s) {
            cos_angle = -cos_angle;
            sin_angle = -sin_angle;
        }
        try_move(0, p->speed * sin_angle);
        try_move(p->speed * cos_angle, 0);

        is_moving = true;
    }
    if (p->btn_a) {
        left_angle = p->angle - PI / 2;
        try_move(0, p->speed * sin(left_angle));
        try_move(p->speed * cos(left_angle), 0);
        
        is_moving = true;
    }
    if (p->btn_d) {
        right_angle = p->angle + PI / 2;
        try_move(0, p->speed * sin(right_angle));
        try_move(p->speed * cos(right_angle), 0);

        is_moving = true;
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
    
    if (is_moving && p->jump_speed == 0) 
    {
        step_progress += step_frequency;
        p->z = base_z + step_amplitude * sin(step_progress);
    } else if(p->jump_speed != 0) {
        p->jump_speed -= 0.01;
    }
    
    p->z += p->jump_speed;
    if (p->z < 0.5)
    {
        p->z = 0.5;
        p->jump_speed = 0;
    }
    p->x = p->x_px / BLOCK_SIZE;
    p->y = p->y_px / BLOCK_SIZE;

    // Update direction vectors based on angle
    p->x_dir = cos(p->angle);
    p->y_dir = sin(p->angle);

    p->direction = p->angle * (180 / PI);
    if (p->direction > 180)
        p->direction -= 360;

    if(p->pause)
        pouse_game();
}