/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:59:10 by escura            #+#    #+#             */
/*   Updated: 2024/09/17 16:29:20 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void init_weapons(t_cube *c)
{
    t_item *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Wooden Sword";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 273;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[273] = *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Stone Sword";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 275;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[275] = *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Pirate Sword";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 279;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[279] = *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Axe";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 24;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[24] = *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Torch";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 33;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    item->right_click = &place;
    c->items[33] = *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Dagger";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 282;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[282] = *item;
}