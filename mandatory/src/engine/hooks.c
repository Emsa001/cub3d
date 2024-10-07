/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:25:04 by escura            #+#    #+#             */
/*   Updated: 2024/10/07 14:38:32 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	kd(int kc)
{
	if (kc == ESC)
		exit_game(0);
	if (kc == W || kc == UP)
		player()->btn_w = true;
	if (kc == S || kc == DOWN)
		player()->btn_s = true;
	if (kc == A)
		player()->btn_a = true;
	if (kc == D)
		player()->btn_d = true;
	if (kc == LEFT)
		player()->btn_left = true;
	if (kc == RIGHT)
		player()->btn_right = true;
	if (kc == SHIFT)
		player()->speed = SPRINTSPEED;
	if (kc == MINUS)
		if (player()->fov > 30)
			player()->fov -= 5;
	if (kc == PLUS)
		if (player()->fov < 120)
			player()->fov += 5;
	return (0);
}

int	ku(int kc)
{
	if (kc == W || kc == UP)
		player()->btn_w = false;
	if (kc == S || kc == DOWN)
		player()->btn_s = false;
	if (kc == A)
		player()->btn_a = false;
	if (kc == D)
		player()->btn_d = false;
	if (kc == SHIFT)
		player()->speed = WALKSPEED;
	if (kc == LEFT)
		player()->btn_left = false;
	if (kc == RIGHT)
		player()->btn_right = false;
	return (0);
}

static int	exit_game_hook(void *arg)
{
	exit_game(0);
	(void)arg;
	return (0);
}

void	init_hooks(void)
{
	const t_cube	*c = cube();

	mlx_do_key_autorepeaton(c->mlx);
	mlx_hook(c->win, KeyPress, KeyPressMask, kd, (void *)c);
	mlx_hook(c->win, KeyRelease, KeyReleaseMask, ku, (void *)c);
	mlx_loop_hook(c->mlx, render_scene, (void *)c);
	mlx_hook(c->win, 17, 0, exit_game_hook, NULL);
	mlx_loop(c->mlx);
}
