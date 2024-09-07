/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:04:28 by escura            #+#    #+#             */
/*   Updated: 2024/09/07 19:16:08 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void init_potions(t_cube *c)
{
    t_item *item;

    item = (t_item *)ft_malloc(sizeof(t_item));
    item->name = "Vision";
    item->fontSize = 0.5;
    item->use = &vision;
    item->props.id = 112;
    item->props.effect = 10; // seconds of effect
    c->items[112] = *item;

}