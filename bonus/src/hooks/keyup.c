/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:21:05 by escura            #+#    #+#             */
/*   Updated: 2024/09/29 15:20:01 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Existing key release function
int	key_up(int keycode)
{
	t_player		*p;
	const t_cube	*c = cube();

	p = player();
	if (keycode == W)
		p->btn_w = false;
	if (keycode == S)
		p->btn_s = false;
	if (keycode == A)
		p->btn_a = false;
	if (keycode == D)
		p->btn_d = false;
	if (keycode == SHIFT)
		p->sprint = false;
	if (keycode == LEFT)
	{
		p->btn_left = false;
	}
	if (keycode == RIGHT)
	{
		p->btn_right = false;
	}
	if (keycode == UP)
		p->btn_up = false;
	if (keycode == DOWN)
		p->btn_down = false;
	if (keycode == SPACE)
		p->jumping = false;
	// if(keycode == F)
	//     p->interact = false;
	if (keycode == I)
		p->spawn = false;
	if (keycode == O)
		p->remove = false;
	if (keycode == Z)
	{
		p->catch = false;
		p->catched = false;
	}
	return (0);
}
