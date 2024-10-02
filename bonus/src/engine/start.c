/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/10/01 16:39:36 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_game(void)
{
	const t_render	*r = render();

	create_image(r, WIDTH, HEIGHT);
	// open_portal(0);
	// open_portal(1);
	// open_portal(2);

	t_string str = {0};
	str.str = "Loading...";
	str.color = 0xFFFFFF;
	str.size = 1;
	str.x = CENTER_WIDTH - ft_strlen(str.str) * 8;
	str.y = CENTER_HEIGHT - 20;
	str.time = 10000;
	render_string_async(&str);

	init_hooks();
	mlx_loop_hook(r->mlx, render_scene_multithread, NULL);
	mlx_loop(r->mlx);
}
