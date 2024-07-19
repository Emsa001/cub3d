/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:25:04 by escura            #+#    #+#             */
/*   Updated: 2024/07/19 21:06:09 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MOUSE_SENSITIVITY 0.002

int mouse_left_click(int button)
{
    t_player *p = player();
    if (button == 1)
        p->catch = true;
    if(button == 3)
    {
        p->catch = false;
        p->catched = false;
    }
    return (0);
}

int mouse_move(int x, int y, t_cube *c)
{
	t_player *p = player();
	int dx = x - WIDTH / 2;
	int dy = y - HEIGHT / 2;

	p->angle += dx * MOUSE_SENSITIVITY;
	if (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	if (p->angle < 0)
		p->angle += 2 * PI;
	if (p->z_dir - dy * MOUSE_SENSITIVITY > -0.5 && p->z_dir - dy * MOUSE_SENSITIVITY < 0.5)
        p->z_dir -= dy * MOUSE_SENSITIVITY;

	mlx_mouse_move(c->mlx, c->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

// Existing key press function
int kd(int kc)
{
    t_player *p = player();

    if (kc == ESC)
        exit_game();
    
    if (kc == W)
        p->btn_w = true;
    if (kc == S)
        p->btn_s = true;
    if (kc == A)
        p->btn_a = true;
    if (kc == D)
        p->btn_d = true;
    
    if(kc == LEFT){
        p->btn_left = true;
    }
    if(kc == RIGHT){
        p->btn_right = true;
    }
    if(kc == UP)
        p->btn_up = true;

    if(kc == DOWN)
        p->btn_down = true;
    
    if(kc == SHIFT)
        p->speed = SPRINTSPEED;
    if(kc == SPACE)
        p->jump = true;

    if(kc == MINUS){
        if(p->fov > 30)
            p->fov -= 5;
    }
    if(kc == PLUS)
        if(p->fov < 120)
            p->fov += 5;
    
    if(kc == E)
        p->interact = true;
    if(kc == I)
        p->spawn = true;
    if(kc == O)
        p->remove = true;
    if(kc == F)
        p->catch = true;

    return (0);
}

// Existing key release function
int ku(int kc)
{
    t_player *p = player();
    
    if (kc == W )
        p->btn_w = false;
    if (kc == S )
        p->btn_s = false;
    if (kc == A)
        p->btn_a = false;
    if (kc == D)
        p->btn_d = false;
    if(kc == SHIFT)
        p->speed = WALKSPEED;
    if(kc == SPACE)
        p->jump = false;
    if(kc == LEFT){
        p->btn_left = false;
    }
    if(kc == RIGHT){
        p->btn_right = false;
    }
    
    if(kc == UP)
        p->btn_up = false;
    if(kc == DOWN)
        p->btn_down = false;

    if(kc == E)
        p->interact = false;
    if(kc == I)
        p->spawn = false;
    if(kc == O)
        p->remove = false;
    if(kc == F)
    {
        p->catch = false;
        p->catched = false;
    }

    return (0);
}

// Initialize hooks including mouse movement hook
void init_hooks(void)
{
    const t_cube *c = cube();

    mlx_do_key_autorepeaton(c->mlx);
    mlx_hook(c->win, KeyPress, KeyPressMask, kd, (void *)c);
    mlx_hook(c->win, KeyRelease, KeyReleaseMask, ku, (void *)c);
    mlx_hook(c->win, MotionNotify, PointerMotionMask, mouse_move, (void *)c);
    mlx_hook(c->win, ButtonPress, ButtonPressMask, mouse_left_click, (void *)c);
    mlx_mouse_hide(c->mlx, c->win);
    mlx_loop_hook(c->mlx, render_scene, (void *)c);
    mlx_loop(c->mlx);
}