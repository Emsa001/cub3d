/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/10/01 12:52:31 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_game(void)
{
	const t_render	*r = render();

	create_image(r, WIDTH, HEIGHT);
	open_portal(0);
	open_portal(1);
	open_portal(2);
	init_hooks();
	mlx_loop_hook(r->mlx, render_scene_multithread, NULL);
	mlx_loop(r->mlx);
}
