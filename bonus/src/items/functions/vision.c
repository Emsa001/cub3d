/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:25:18 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 18:16:51 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "items.h"
#include "cub3d.h"

void vision_end(void *arg)
{
    player()->vision = false;
}

void vision(t_itemprops props)
{
    t_player *p = player();
    p->inventory[props.playerslot] = -1;
    p->vision = true;

    int seconds = props.effect;

    async_t async;
    async.function = &vision_end;
    async.arg = NULL;
    async.time = seconds * 60 * cube()->delta_time;
    async.icon = textures()->items[props.id];
    add_async(async);
}