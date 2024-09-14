/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 21:57:37 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void end_mt(){
    printf("End from main thread\n");

    t_textures *t = textures();
    // open_portal(1);
    t_image img;
    img.x = 0;
    img.y = 0;
    img.size = 1;
    img.img = t->ui->home;
    img.time = 1000;
    render_image_async(&img);
    // open_portal(1);
}

void process_test(){
	printf("hello from process\n");
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
    
    // t_async *async = new_async();
    // async->end = &end;
    // async->end_mt = &end_mt;
    // async->time = 5000;
    // start_async(async);

    t_async *async2 = new_async();
    async2->end = &end_mt;
    async2->process = &process_test;
    async2->time = 1000;
    start_async_process(async2);
    
    t_textures *t = textures();


    t_image img;
    img.x = 0;
    img.y = 0;
    img.size = 3;
    img.img = t->ui->home;
    img.time = 1000;
    render_image_async(&img);

    // open_portal(0);
    // open_portal(1);
    

    mlx_loop_hook(r->mlx, render_scene_multithread, NULL);
    mlx_loop(r->mlx);
}
