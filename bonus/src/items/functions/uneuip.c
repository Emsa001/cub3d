/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uneuip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:27:00 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 19:33:57 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "items.h"
#include "cub3d.h"


void unequip(void *props)
{
    t_player *p = player();
    int index = (int)props;
    t_item item = cube()->items[p->equipped[index]];

    printf("Unequipping item %d\n", index);
    for(int i = 0; i < 9; i++)
    {
        if (p->inventory[i] == -1)
        {
            p->inventory[i] = p->equipped[index];
            break;
        }
    }
    p->speed -= item.props.effect;
    p->equipped[index] = -1;

}