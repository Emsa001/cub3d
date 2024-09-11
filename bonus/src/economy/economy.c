/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   economy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:58:36 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 16:17:13 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void process(t_async *current){
    int time_left = (current->time - current->time_elapsed);
    current->player->money += current->cube->add_money;
}

void init_economy(){
    t_async *async = (t_async *)ft_calloc(sizeof(t_async), 1);
    async->process = &process;
    async->process_time = 1000; // 1 second
    async->time = -1;
    add_async(async);
}