/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 16:08:48 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void start_game(void)
{
    t_render *r = render();
    t_cube *c = cube();
    
    create_image(r, WIDTH, HEIGHT);
    // sleep(1);

    init_hooks();
    init_economy();


    mlx_loop_hook(r->mlx, render_scene_multithread, NULL);
    mlx_loop(r->mlx);
}
