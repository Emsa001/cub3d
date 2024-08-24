/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:16:29 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 19:32:46 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "items.h"
#include "cub3d.h"


void init_items()
{
    t_cube *c = cube();  // Assuming this function initializes the t_cube structure
    const t_textures *t = textures();  // Assuming this function initializes textures
    t_item *item;

    // Allocate and initialize item with id 0
    item = (t_item *)ft_malloc(sizeof(t_item));
    item->use = &instand_death;
    item->props.id = 0;
    item->props.slot = -1;
    c->items[0] = *item;

    // Allocate and initialize item with id 28
    item = (t_item *)ft_malloc(sizeof(t_item));
    item->use = &cure;
    item->props.id = 30;
    item->props.effect = 20;
    c->items[28] = *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->use = &equip;
    item->props.id = 36;  // Directly assign values
    item->props.slot = 3;
    item->props.effect = 10;
    c->items[36] = *item;

}

void useItem(void *arg)
{
    int index = (int)arg;
    int id =  player()->inventory[index];
    player()->inventory[index] = -1;
    
    t_item i = cube()->items[id];
    i.use(i.props);
}
