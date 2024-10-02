/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:44:25 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 18:22:32 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	handle_pause_controlls(int keycode, t_player *p, t_cube *c)
{
	if (keycode == ESC)
	{
		if(p->gui != NONE && p->gui != PAUSE)
		{
			p->gui = NONE;
			return false;
		}
		p->gui = NONE;
		set_paused(!c->paused);
	}
	if (is_paused()){
		p->gui = PAUSE;
		return (true);
	}
	return (false);
}

static void stop_slide(){
	t_player *p = player();
	p->slide = false;
}

static void	handle_movement_controlls(int keycode, t_player *p)
{
	if (keycode == W)
		p->btn_w = true;
	if (keycode == S)
		p->btn_s = true;
	if (keycode == A)
		p->btn_a = true;
	if (keycode == D)
		p->btn_d = true;
	if (keycode == LEFT)
		p->btn_left = true;
	if (keycode == RIGHT)
		p->btn_right = true;
	if (keycode == UP)
		p->btn_up = true;
	if (keycode == DOWN)
		p->btn_down = true;
	if (keycode == SHIFT)
		p->sprint = true;
	if (keycode == SPACE)
		p->jumping = true;
	if(keycode == CTRL){
		p->slide = true;
		ft_wait(500, &stop_slide, NULL);
	}
}

static bool	handle_gui_controlls(int keycode, t_player *p)
{
	if (keycode == G)
	{
		if (p->gui == MATH)
			return (true);
		if (p->gui_temp != NONE && p->gui == NONE)
			p->gui = p->gui_temp;
		else
			p->gui = NONE;
	}
	if (keycode == E)
	{
		if (p->gui == MATH)
			return (true);
		if (p->gui == NONE)
			p->gui = INVENTORY;
		else
			p->gui = NONE;
	}
	return (false);
}

static void	handle_interaction_controlls(int keycode, t_player *p)
{
	if (keycode == E)
		p->interact = true;
	if (keycode == I)
		p->spawn = true;
	if (keycode == O)
		p->remove = true;
	if (keycode == F)
		p->interact = true;
	if (keycode == Z)
		p->catch = true;
}

int	key_down(int keycode)
{
	t_player	*p;

	p = player();
	if (handle_pause_controlls(keycode, p, cube()))
		return (0);
	if (handle_gui_controlls(keycode, p))
		return (0);
	handle_movement_controlls(keycode, p);
	handle_interaction_controlls(keycode, p);
	return (0);
}
