/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:53:45 by btvildia          #+#    #+#             */
/*   Updated: 2024/08/16 12:32:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// it gets max 3 when the angle is 45, 135, 225, 315
// it gets min 1 when the angle is 0, 90, 180, 270
// it changes value between 1 and 3 every time the angle changes

int get_block_id(t_block *blocks, float px, float py, float angle)
{
    int i = 0;
    float x = 0;
    float y = 0;
    float p_x = px - 0.5 + 2.5 * cos(angle);
    float p_y = py - 0.5 + 2.5 * sin(angle);

    float full_angle = angle * 180 / PI;

    float md = 2 + (-cos(angle * PI / 45));

    while (blocks[i].x != -1)
    {
        x = blocks[i].x;
        y = blocks[i].y;
        if ((p_x - md <= x && x <= p_x + md) && (p_y - md <= y && y <= p_y + md))
            return i;
        i++;
    }
    return -1;
}

void catch_block(float angle)
{
    t_player *p = player();
    t_cube *c = cube();
    static int id;

    if (!c->map->blocks)
        return;
    if (!p->catched)
    {
        id = get_block_id(c->map->blocks, p->x, p->y, angle);
        p->catched = true;
    }
    if (id == -1)
    {
        p->catched = false;
        return;
    }
    c->map->blocks[id].x = p->x - 0.5 + 2.5 * cos(angle);
    c->map->blocks[id].y = p->y - 0.5 + 2.5 * sin(angle);
}
