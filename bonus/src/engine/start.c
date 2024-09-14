/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 15:01:00 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xlib.h>
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
    init_hooks();
    init_economy();
    // add_sprite("assets/fire/", 13,7,21);
    
    t_async *async = (t_async *)ft_calloc(sizeof(t_async), 1);
    async->start = &start;
    async->end = &end;
    async->time = 1000;
    add_async(async);

    

    // add_sprite("assets/torch/", 9, 5, 5);
    // add_sprite("assets/fire/", 13, 3, 4);
    // add_sprite("assets/portal/", 17, 4, 3);

    // t_string str;
    // str.str = "Hello World!";
    // str.size = 2;
    // str.x =CENTER_WIDTH;
    // str.y = CENTER_HEIGHT;
    // str.color = 0x00FF00;
    // str.time = 3000;
    // write_string_seconds(&str);

    // mlx_loop_hook(r->mlx, render_scene_singlethread, (void *)c);
    mlx_loop_hook(r->mlx, render_scene_multithread, (void *)c);
    mlx_loop(r->mlx);
}
