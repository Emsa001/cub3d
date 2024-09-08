/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/08 21:15:16 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void start(void){
	printf("start async\n");
}

void end(void){
	printf("end async\n");
}

void process(t_async *current){
    int time_left = (current->time - current->time_elapsed);


    if(time_left % 1000 == 0){
        current->player->money += current->cube->add_money;
    }
}

void start_game(void)
{
    t_render *r = render();
    t_cube *c = cube();
    init_hooks();
    // start the game

    t_async *async = (t_async *)ft_malloc(sizeof(t_async));
    async->start = &start;
    async->process = &process;
    async->end = &end;
    async->arg = NULL;
    async->time = 30000 * 1000;
    add_async(async);

    // mlx_loop_hook(r->mlx, render_scene_singlethread, (void *)c);
    mlx_loop_hook(r->mlx, render_scene_multithread, (void *)c);
    mlx_loop(r->mlx);
}
