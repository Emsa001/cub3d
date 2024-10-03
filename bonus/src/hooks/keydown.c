/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:44:25 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 18:44:08 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (keycode == CTRL)
	{
		p->slide = true;
		ft_wait(500, &stop_slide, NULL);
	}
}

static void	handle_interaction_controlls(int keycode, t_player *p)
{
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
	if (handle_pause_controlls(keycode, p))
		return (0);
	if (handle_gui_controlls(keycode, p))
		return (0);
	handle_movement_controlls(keycode, p);
	handle_interaction_controlls(keycode, p);
	return (0);
}
