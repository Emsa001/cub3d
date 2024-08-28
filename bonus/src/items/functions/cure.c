/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cure.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:25:18 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 18:17:25 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "items.h"
#include "cub3d.h"

void cure(t_itemprops props)
{
    t_player *p = player();
    p->inventory[props.playerslot] = -1;

    p->health += props.effect;
    if (p->health > 100)
        p->health = 100;
}