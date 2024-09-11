/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 18:06:25 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void end(){
    add_sprite("assets/torch/", 9, 5, 5);
    add_sprite("assets/fire/", 13, 3, 4);
    // add_sprite("assets/portal/", 17, 4, 3);
    printf("placed\n");;
}

void start_game(void)
{
    t_render *r = render();
    t_cube *c = cube();
    init_hooks();
    init_economy();

    t_async *async = (t_async *)ft_calloc(sizeof(t_async), 1);
    async->end = &end;
    async->time = 2000;
    add_async(async);

    // add_sprite("assets/torch/", 9, 5, 5);
    // add_sprite("assets/fire/", 13, 3, 4);
    // add_sprite("assets/portal/", 17, 4, 3);

    // mlx_loop_hook(r->mlx, render_scene_singlethread, (void *)c);
    mlx_loop_hook(r->mlx, render_scene_multithread, (void *)c);
    mlx_loop(r->mlx);
}
