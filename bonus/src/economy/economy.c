/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   economy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:58:36 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 14:59:47 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void start(void){
	printf("Economy hooked\n");
}

void process(t_async *current){
    int time_left = (current->time - current->time_elapsed);
    current->player->money += current->cube->add_money;
}

void init_economy(){
    t_async *async = (t_async *)ft_malloc(sizeof(t_async));
    async->start = &start;
    async->process = &process;
    async->end = NULL;
    async->arg = NULL;
    async->time = -1;
    async->process_time = 1000; // 1 second
    add_async(async);
}