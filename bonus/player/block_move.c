/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:53:45 by btvildia          #+#    #+#             */
/*   Updated: 2024/07/18 18:40:56 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void spawn_block(float angle, int i)
{
    t_player *p = player();
    t_cube *c = cube();
    t_map *map = c->map;

    float x = 0;
    float y = 0;

    x = p->x - 0.5 + 2.5 * cos(angle);
    y = p->y - 0.5 + 2.5 * sin(angle);
    
    if(i == 1)
        add_block(x, y);
    // else
        // remove_block(x, y);
}


// it gets max 3 when the angle is 45, 135, 225, 315
// it gets min 1 when the angle is 0, 90, 180, 270
// it changes value between 1 and 3 every time the angle changes

int get_block_id(t_block *blocks, float px, float py, float angle)
{
    int id = -1;
    int i = 0;
    float x = 0;
    float y = 0;
    float p_x = px - 0.5 + 2.5 * cos(angle);
    float p_y = py - 0.5 + 2.5 * sin(angle);

    float full_angle = angle * 180 / PI;

    float missing_distance = 2 +(-cos(angle * PI / 45));

    while(blocks[i].x != -1)
    {
        x = blocks[i].x;
        y = blocks[i].y;
        if((p_x - missing_distance <= x && x <= p_x + missing_distance) && (p_y - missing_distance <= y && y <= p_y + missing_distance))
            return i;
        i++;
    }

    return id;
}

void catch_block(float angle)
{
    t_player *p = player();
    t_cube *c = cube();
    
    if(!c->map->blocks)
        return;
    
    int id = 0;
    id = get_block_id(c->map->blocks, p->x, p->y, angle);
    if(id == -1)
        return;
    
    c->map->blocks[id].x = p->x -0.5 + 2.5 * cos(angle);
    c->map->blocks[id].y = p->y -0.5 + 2.5 * sin(angle);
}
