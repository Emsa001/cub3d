/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/17 21:40:17 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void end(){
    printf("End from async\n");
}

void end_mt(){
    printf("End from main thread\n");
    open_portal(1);
    open_portal(0);
}

void start_game(void)
{
    t_render *r = render();
    t_cube *c = cube();
    
    create_image(r, WIDTH, HEIGHT);
    // sleep(1);

    init_hooks();
    init_economy();
    // add_sprite("assets/fire/", 13,7,37);
    
    // t_async *async = new_async();
    // async->end = &end;
    // async->end_mt = &end_mt;
    // async->time = 3000;
    // start_async(async);

    // open_portal(0);
    // open_portal(1);
    

    mlx_loop_hook(r->mlx, render_scene_multithread, NULL);
    mlx_loop(r->mlx);
}
