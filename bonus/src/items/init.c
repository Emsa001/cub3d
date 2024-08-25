/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:16:29 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 18:24:32 by escura           ###   ########.fr       */
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
    item->tooltip = "Instant death";
    item->fontSize = 0.5;
    item->use = &instand_death;
    item->props.id = 0;
    item->props.slot = -1;
    c->items[0] = *item;

    // Allocate and initialize item with id 28
    item = (t_item *)ft_malloc(sizeof(t_item));
    item->tooltip = "Cure";
    item->fontSize = 0.5;
    item->use = &cure;
    item->props.id = 30;
    item->props.effect = 20;
    c->items[28] = *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->tooltip = "Boots of speed";
    item->fontSize = 0.37;
    item->use = &equip;
    item->props.id = 37;
    item->props.slot = BOOTS;
    item->props.effect = 10; // + to speed
    c->items[37] = *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->tooltip = "Wooden Sword";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 49;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[49] = *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->tooltip = "Stone Sword";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 50;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[50] = *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->tooltip = "Pirate Sword";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 53;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[53] = *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->tooltip = "Axe";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 59;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[59] = *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->tooltip = "Torch";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 129;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[129] = *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->tooltip = "Dagger";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 57;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[57] = *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->tooltip = "Vision";
    item->fontSize = 0.5;
    item->use = &vision;
    item->props.id = 112;
    item->props.effect = 10; // seconds of effect
    c->items[112] = *item;

}

void useItem(void *arg)
{
    int index = (int)arg;
    int id =  player()->inventory[index];
    // player()->inventory[index] = -1;
    
    t_item i = cube()->items[id];
    i.props.playerslot = index;
    i.use(i.props);
}
