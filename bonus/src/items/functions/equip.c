/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:27:00 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 19:32:58 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "items.h"
#include "cub3d.h"


void equip(t_itemprops props)
{
    t_player *p = player();

    printf("Equipping item %d in slot %d\n", props.id, props.slot);

    if (p->equipped[props.slot] != -1)
        return;

    p->equipped[props.slot] = props.id;
    p->speed += props.effect;
}