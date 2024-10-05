/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:34:18 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 18:12:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	exit_game_hook(void *arg)
{
	(void)arg;
	exit_game(0);
	return (0);
}

void	init_hooks(void)
{
	const t_render	*r = render();
	const t_cube	*c = cube();

	mlx_do_key_autorepeaton(r->mlx);
	mlx_hook(r->win, KeyPress, KeyPressMask, key_down, (void *)c);
	mlx_hook(r->win, KeyRelease, KeyReleaseMask, key_up, (void *)c);
	mlx_hook(r->win, MotionNotify, PointerMotionMask, mouse_move, (void *)c);
	mlx_hook(r->win, ButtonPress, ButtonPressMask, mouse_click, (void *)c);
	mlx_hook(r->win, 17, 0, exit_game_hook, NULL);
}
