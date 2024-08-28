/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   armor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:06:38 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 19:09:04 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void init_armor(t_cube *c)
{
    t_item *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->name = "Boots of speed";
    item->fontSize = 0.37;
    item->use = &equip;
    item->props.id = 37;
    item->props.slot = BOOTS;
    item->props.effect = 10; // + to speed
    c->items[37] = *item;
}