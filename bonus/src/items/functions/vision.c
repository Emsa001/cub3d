/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:25:18 by escura            #+#    #+#             */
/*   Updated: 2024/09/08 18:43:06 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "items.h"
#include "cub3d.h"

void vision_start(t_async *current)
{
    // player()->vision = true;
}

void vision_process(t_async *current){
    // VISION CAUSES DATA RACE
    current->player->vision = true;
    const t_texture *t = textures()->items[112];

    const int left_time = current->time - current->time_elapsed;

    float size = 5.0f - (5.0f - 0.1f) * ((float)current->time_elapsed / current->time);
    if (size < 0.1f) {
        size = 0.1f;
    }

    int new_width = (int)(t->width * size);
    int new_height = (int)(t->height * size);
    int new_x = WIDTH - 100 + (t->width - new_width) / 2 - current->id * 100;
    int new_y = HEIGHT - 100 + (t->height - new_height) / 2;

    add_image_queue(t, new_x, new_y, size, current->render);
}

void vision_end(t_async *current)
{
    current->player->vision = true;
}

void vision(t_itemprops props)
{
    t_player *p = player();
    p->inventory[props.playerslot] = -1;

    t_async *async = (t_async *)ft_malloc(sizeof(t_async));
    async->start = &vision_start;
    async->process = &vision_process;
    async->end = &vision_end;
    async->arg = NULL;
    async->time = props.effect;
    add_async(async);
}