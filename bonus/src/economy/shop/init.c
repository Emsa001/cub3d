/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:07:56 by escura            #+#    #+#             */
/*   Updated: 2024/09/19 17:40:50 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_store *init_store()
{
    t_store *store = ft_malloc(sizeof(t_store));
    store->open = false;
    store->can_open = false;
    store->case_cooldown = false;
    pthread_mutex_init(&store->case_mutex, NULL);

    int i = 0;
    while(i < 27)
    {
        store->items[i] = 1;
        i++;
    }

    i = 0;
    while(i < 3)
    {
        store->cases[i] = 146;
        i++;
    }

    i = 0;
    while(i < 2)
    {
        store->generators[i] = 147;
        i++;
    }
    t_point *points = get_points(cube()->map->map, 'M');
    store->x = points[0].x;
    store->y = points[0].y;

    return store;
}