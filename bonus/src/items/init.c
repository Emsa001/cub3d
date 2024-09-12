/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:16:29 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 14:35:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void init_items()
{
    t_cube *c = cube();

    init_armor(c);
    init_potions(c);
    init_weapons(c);
}

void useItem(void *arg)
{
    int index = (int)(intptr_t)arg;
    int id =  player()->inventory[index];
    
    t_item i = cube()->items[id];
    i.props.playerslot = index;
    if(i.use != NULL)
        i.use(i.props);
}

void item_tooltip(void *arg)
{
    t_player *p = player();
    int index = p->hover->itemId;
    t_item *item = &cube()->items[index];

    tooltip(item->name, item->fontSize);
}