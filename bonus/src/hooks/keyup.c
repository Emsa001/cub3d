/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:21:05 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 15:55:37 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement_controlls(int keycode, t_player *p)
{
	if (keycode == W)
		p->btn_w = false;
	if (keycode == S)
		p->btn_s = false;
	if (keycode == A)
		p->btn_a = false;
	if (keycode == D)
		p->btn_d = false;
	if (keycode == LEFT)
		p->btn_left = false;
	if (keycode == RIGHT)
		p->btn_right = false;
	if (keycode == UP)
		p->btn_up = false;
	if (keycode == DOWN)
		p->btn_down = false;
	if (keycode == SPACE)
		p->jumping = false;
}

static void	handle_interaction_controlls(int keycode, t_player *p)
{
	// if (keycode == F)
	// 	p->interact = false;
	if (keycode == I)
		p->spawn = false;
	if (keycode == O)
		p->remove = false;
	if (keycode == Z)
	{
		p->catch = false;
		p->catched = false;
	}
}

int	key_up(int keycode)
{
	t_player	*p;

	p = player();
	handle_movement_controlls(keycode, p);
	handle_interaction_controlls(keycode, p);
	return (0);
}
