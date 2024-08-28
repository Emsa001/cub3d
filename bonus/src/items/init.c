/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:16:29 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 19:10:10 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

t_item *new_item(char *name){
    t_item *item = (t_item *)ft_malloc(sizeof(t_item));
    item->name = "Instant death";
    item->fontSize = 0.5;
    item->use = &instand_death;
    item->props.id = 0;
    item->props.slot = -1;
    return item;
}

void init_items()
{
    t_cube *c = cube();

    init_armor(c);
    init_potions(c);
    init_weapons(c);
}

void useItem(void *arg)
{
    int index = (int)arg;
    int id =  player()->inventory[index];
    
    t_item i = cube()->items[id];
    i.props.playerslot = index;
    i.use(i.props);
}
