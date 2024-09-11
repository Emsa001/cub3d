/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 22:58:02 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xlib.h>
#include "cub3d.h"


void start(){
    add_sprite("assets/fire/", 13, 7, 7);
    printf("placed\n");
}

void end(){
    remove_sprite(7, 7);
    usleep(2000000);
    remove_sprite(4, 1);
    add_sprite("assets/portal_opened/", 17, 4, 1);
    printf("removed\n");
}

void start_game(void)
{
    t_render *r = render();
    t_cube *c = cube();
    init_hooks();
    init_economy();

    t_async *async = (t_async *)ft_calloc(sizeof(t_async), 1);
    async->start = &start;
    async->end = &end;
    async->time = 3000;
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
