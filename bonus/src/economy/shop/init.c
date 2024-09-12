/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:07:56 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 21:49:24 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_store *init_store()
{
    t_store *store = malloc(sizeof(t_store));
    store->open = false;
    store->can_open = false;

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

    store->x = 7;
    store->y = 18;
    add_sprite("assets/shop/", 28, store->x, store->y);

    return store;
}