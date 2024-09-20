/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:52:13 by escura            #+#    #+#             */
/*   Updated: 2024/09/20 12:37:31 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_generator *create_generator(int x, int y)
{
    printf("Create generator at %d %d\n", x, y);
    t_generator *gen = ft_malloc(sizeof(t_generator));
    gen->x = x;
    gen->y = y;
    
    gen->generated = 0;
    gen->energy = 0;
    gen->add_money = 10;

    gen->level = 1;
    gen->speed = 1;

    gen->loop = 0;

    gen->next = NULL;
    pthread_mutex_init(&gen->mutex, NULL);

    cube()->add_money += gen->add_money;

    t_async *async = new_async();
    async->process = &generator_generating;
    async->process_time = 1000;
    async->arg = (void *)gen;
    async->time = -1;
    async->cube = cube();
    async->player = player();

    start_async(async);

    return gen;
}

t_generator *get_generator(int x, int y)
{
    t_player *p = player();
    t_generator *gen = p->store->generators;
    t_generator *last_gen = NULL;

    while(gen)
    {
        if(gen->x == x && gen->y == y)
            return gen;
        last_gen = gen;
        gen = gen->next;
    }

    gen = create_generator(x, y);
    
    if (p->store->generators == NULL) {
        p->store->generators = gen;
    } else {
        last_gen->next = gen;
    }
    
    return gen;
}

int gen_total_amount()
{
    t_player *p = player();
    t_generator *gen = p->store->generators;
    int total = 0;

    while(gen){
        total += (gen->add_money / 5) * gen->speed;
        gen = gen->next;
    }

    return total;
}