/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:07:56 by escura            #+#    #+#             */
/*   Updated: 2024/09/27 20:20:00 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_store *init_store()
{
    t_store *store = ft_malloc(sizeof(t_store));
    store->case_cooldown = false;
    pthread_mutex_init(&store->case_mutex, NULL);

    int items[27] = {
        33, 169, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26
    };
    int i = 0;
    while(i < 27)
    {
        store->items[i] = items[i];
        i++;
    }

    store->generators = NULL;
    return store;
}