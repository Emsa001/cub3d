/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 19:52:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	loading(void)
// {
// 	t_string	str;

// 	str = (t_string){0};
// 	str.str = "Loading...";
// 	str.color = 0xFFFFFF;
// 	str.size = 1;
// 	str.x = CENTER_WIDTH - ft_strlen(str.str) * 8;
// 	str.y = CENTER_HEIGHT - 20;
// 	str.time = 10000;
// 	render_string_async(&str);
// }

void	start_game(void)
{
	t_render *const	r = render();

	create_image(r, WIDTH, HEIGHT);
	init_hooks();
	mlx_loop_hook(r->mlx, render_scene_multithread, NULL);
	mlx_loop(r->mlx);
}
