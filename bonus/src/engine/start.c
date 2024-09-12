/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 21:53:02 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xlib.h>
#include "cub3d.h"

void test(){
    printf("tasdasdest\n");
}

void start_game(void)
{
    t_render *r = render();
    t_cube *c = cube();
    // init_economy();
    init_hooks();

    t_async *async = (t_async *)ft_calloc(sizeof(t_async), 1);
    async->end = &test;
    async->time = 100000000;
    add_async(async);

    // t_async *async2 = (t_async *)ft_calloc(sizeof(t_async), 1);
    // async2->end = &test;
    // async2->time = 10000000;
    // add_async(async2);

    // t_async *async3 = (t_async *)ft_calloc(sizeof(t_async), 1);
    // async3->end = &test;
    // async3->time = 10000000;
    // add_async(async3);

    exit_game(0);

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
