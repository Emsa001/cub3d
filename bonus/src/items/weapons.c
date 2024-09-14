/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:59:10 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 13:54:35 by escura           ###   ########.fr       */
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
    item->props.id = 49;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[49] = *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Stone Sword";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 50;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[50] = *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Pirate Sword";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 53;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[53] = *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Axe";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 59;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[59] = *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Torch";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 129;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    item->right_click = &place;
    c->items[129] = *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Dagger";
    item->fontSize = 0.4;
    item->use = &equip;
    item->props.id = 57;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[57] = *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Netherite Sword";
    item->fontSize = 0.35;
    item->use = &equip;
    item->props.id = 255;
    item->props.slot = WEAPON;
    item->props.effect = 10;
    c->items[255] = *item;
}