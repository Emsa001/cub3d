/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 17:39:27 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void start(){
    printf("Start\n");
    // remove_sprite(4, 19);
    // add_sprite("assets/portal_opened/", 17, 4, 19);
}

void end(){
    open_portal(0);
    open_portal(1);
}

void start_game(void)
{
    t_render *r = render();
    t_cube *c = cube();
    
    create_image(r, WIDTH, HEIGHT);
    // sleep(1);

    init_hooks();
    init_economy();
    // add_sprite("assets/fire/", 13,7,21);
    
    t_async *async = new_async();
    async->start = &start;
    async->end = &end;
    async->time = 2000;
    start_async(async);

    

    mlx_loop_hook(r->mlx, render_scene_multithread, NULL);
    mlx_loop(r->mlx);
}
