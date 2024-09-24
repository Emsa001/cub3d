/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:04:34 by escura            #+#    #+#             */
/*   Updated: 2024/09/19 19:47:59 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void try_open_door(t_item *item)
{
    t_cube *c = cube();
    t_player *p = player();

    printf("Trying to open door with %s\n", item->name);
}

void init_keys_items(t_cube *c)
{
    t_item *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Old Key";
    item->fontSize = 0.5;
    item->props.id = 50;
    item->right_click = &try_open_door;
    // item->props.effect = 3000;
    c->items[50] = *item;
}