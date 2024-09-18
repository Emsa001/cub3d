/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:07:56 by escura            #+#    #+#             */
/*   Updated: 2024/09/18 19:00:44 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_store *init_store()
{
    t_store *store = ft_malloc(sizeof(t_store));
    store->case_cooldown = false;
    pthread_mutex_init(&store->case_mutex, NULL);

    int i = 0;
    while(i < 27)
    {
        store->items[i] = 1;
        i++;
    }

    store->generators = NULL;
    store->x = 7;
    store->y = 35;
    add_sprite("assets/shop/", 28, store->x, store->y);

    return store;
}