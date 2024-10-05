/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 18:50:27 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_game(void)
{
	t_render *const	r = render();

	r->loading = true;
	cube()->accept_hooks = false;
	create_image(r, WIDTH, HEIGHT);
	init_hooks();
	loading_screen();
	mlx_loop_hook(r->mlx, render_scene_multithread, NULL);
	mlx_loop(r->mlx);
}
