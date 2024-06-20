/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:25:04 by escura            #+#    #+#             */
/*   Updated: 2024/06/20 14:35:40 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	kd(int kc)
{
	t_player *p = player();

	if (kc == ESC)
		exit_game();
	
	if (kc == W || kc == UP)
		p->btn_w = true;
	if (kc == S || kc == DOWN)
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
	
	if(kc == SHIFT)
		p->speed = SPRINTSPEED;

	if(kc == MINUS){
		if(p->fov > 30)
			p->fov -= 5;
	}
	if(kc == PLUS)
		if(p->fov < 120)
			p->fov += 5;

	return (0);
}

int	ku(int kc)
{
	t_player *p = player();
	
	if (kc == W || kc == UP)
		p->btn_w = false;
	if (kc == S || kc == DOWN)
        p->btn_s = false;
	if (kc == A)
        p->btn_a = false;
	if (kc == D)
        p->btn_d = false;
	if(kc == SHIFT)
		p->speed = WALKSPEED;

	if(kc == LEFT){
		p->btn_left = false;
	}
	if(kc == RIGHT){
		p->btn_right = false;
	}

	return (0);
}

void init_hooks(void)
{
    const t_cube *c = cube();
    
    mlx_do_key_autorepeaton(c->mlx);
	mlx_hook(c->win, KeyPress, KeyPressMask, kd, (void *)c);
	mlx_hook(c->win, KeyRelease, KeyReleaseMask, ku, (void *)c);
	mlx_loop_hook(c->mlx, render, (void *)c);
	mlx_loop(c->mlx);
}