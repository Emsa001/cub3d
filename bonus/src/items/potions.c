/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:04:28 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 13:59:51 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void init_potions(t_cube *c)
{
    t_item *item;

    item = (t_item *)ft_calloc(sizeof(t_item),1);
    item->name = "Vision";
    item->fontSize = 0.5;
    item->props.id = 112;
    item->props.effect = 3000;
    c->items[112] = *item;
}