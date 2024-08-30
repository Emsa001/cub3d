/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/08/30 19:05:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void start_game(void)
{
    t_render *r = render();
    t_cube *c = cube();
    init_hooks();
    init_async_queue();
    // start the game

    // mlx_loop_hook(r->mlx, render_scene_singlethread, (void *)c);
    mlx_loop_hook(r->mlx, render_scene_multithread, (void *)c);
    mlx_loop(r->mlx);
}
