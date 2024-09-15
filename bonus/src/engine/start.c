/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/15 14:45:31 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void openPortals(){
    open_portal(1);
    // open_portal(1);
}

void start_game(void)
{
    t_render *r = render();
    t_cube *c = cube();
    
    create_image(r, WIDTH, HEIGHT);

    init_hooks();
    init_economy();

    ft_wait(5000,openPortals);

    mlx_loop_hook(r->mlx, render_scene_multithread, NULL);
    mlx_loop(r->mlx);
}
