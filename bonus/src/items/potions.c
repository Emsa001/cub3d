/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:04:28 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 19:10:07 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void init_potions(t_cube *c)
{
    t_item *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->name = "Instant death";
    item->fontSize = 0.5;
    item->use = &instand_death;
    item->props.id = 0;
    item->props.slot = -1;
    c->items[0] = *item;

    // Allocate and initialize item with id 28
    item = (t_item *)ft_malloc(sizeof(t_item));
    item->name = "Cure";
    item->fontSize = 0.5;
    item->use = &cure;
    item->props.id = 30;
    item->props.effect = 20;
    c->items[28] = *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->name = "Vision";
    item->fontSize = 0.5;
    item->use = &vision;
    item->props.id = 112;
    item->props.effect = 10; // seconds of effect
    c->items[112] = *item;

}