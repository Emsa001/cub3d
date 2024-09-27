/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:44:25 by escura            #+#    #+#             */
/*   Updated: 2024/09/27 18:54:01 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Existing key press function
int	key_down(int keycode)
{
	t_player	*p;
	t_cube		*c;

	p = player();
	c = cube();
	if (keycode == ESC)
	{
		// exit_game(0);
		// return ;
		if (p->GUI == NONE)
			p->GUI = PAUSE;
		else
			p->GUI = NONE;
		set_paused(!c->paused);
	}
	if (is_paused())
		return (0);
	if (keycode == W)
		p->btn_w = true;
	if (keycode == S)
		p->btn_s = true;
	if (keycode == A)
		p->btn_a = true;
	if (keycode == D)
		p->btn_d = true;
	if (keycode == LEFT)
	{
		p->btn_left = true;
	}
	if (keycode == RIGHT)
	{
		p->btn_right = true;
	}
	if (keycode == UP)
		p->btn_up = true;
	if (keycode == DOWN)
		p->btn_down = true;
	if (keycode == SHIFT)
		p->sprint = true;
	if (keycode == SPACE)
		p->jumping = true;
	// if(keycode == MINUS){
	//     if(p->fov > 30)
	//         p->fov -= 5;
	// }
	// if(keycode == PLUS)
	//     if(p->fov < 90)
	//         p->fov += 5;
	if (keycode == E)
	{
		if (p->GUI == MATH)
			return (0);
		if (p->GUI == NONE)
			p->GUI = INVENTORY;
		else
			p->GUI = NONE;
		p->interact = true;
	}
	if (keycode == I)
		p->spawn = true;
	if (keycode == O)
		p->remove = true;
	if (keycode == F)
		p->interact = !p->interact;
	if (keycode == Z)
		p->catch = true;
	if (keycode == G)
	{
		if (p->GUI == MATH)
			return (0);
		if (p->GUI_temp != NONE && p->GUI == NONE)
			p->GUI = p->GUI_temp;
		else
			p->GUI = NONE;
	}
	if (keycode == CTRL)
	{
	}
	return (0);
}
