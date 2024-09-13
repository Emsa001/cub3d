/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/13 21:57:26 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xlib.h>
#include "cub3d.h"

void process2(){
    printf("Hello World\n");
}

void start_game(void)
{
    t_render *r = render();
    t_cube *c = cube();
    
    create_image(r, WIDTH, HEIGHT);

    init_hooks();
    init_economy();

    mlx_loop_hook(r->mlx, render_scene_multithread, NULL);
    mlx_loop(r->mlx);
}
