/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:25:04 by escura            #+#    #+#             */
/*   Updated: 2024/06/18 19:34:31 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	kd(int kc)
{
	if (kc == ESC)
		exit_game();
	if (kc == W)
		player()->btn_w = true;
	if (kc == S)
		player()->btn_s = true;
	if (kc == A)
		player()->btn_a = true;
	if (kc == D)
		player()->btn_d = true;
	return (0);
}

int	ku(int kc)
{
	if (kc == W)
		player()->btn_w = false;
	if (kc == S)
        player()->btn_s = false;
	if (kc == A)
        player()->btn_a = false;
	if (kc == D)
        player()->btn_d = false;
	return (0);
}

void init_hooks(void)
{
    const t_cube *c = cube();
    
    mlx_do_key_autorepeaton(c->mlx);
	mlx_hook(c->win, KeyPress, KeyPressMask, kd, (void *)c);
	mlx_hook(c->win, KeyRelease, KeyReleaseMask, ku, (void *)c);
	mlx_loop_hook(c->mlx, draw, (void *)c);
	mlx_loop(c->mlx);
}