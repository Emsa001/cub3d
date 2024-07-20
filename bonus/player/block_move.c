/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:53:45 by btvildia          #+#    #+#             */
/*   Updated: 2024/07/20 15:54:51 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void remove_block(float angle)
{
    t_player *p = player();
    t_cube *c = cube();
    int id = get_block_id(c->map->blocks, p->x, p->y, angle);
    t_block *new_blocks;
    t_block *tmp;
    t_block *blocks = c->map->blocks;
    int i = 0;
    int j = 0;
    
    if(id == -1)
        return;
    new_blocks = ft_malloc(sizeof(t_block) * (block_count(c->map, '2')));
    while(blocks[i].x != -1)
    {
        if(i != id)
        {
            new_blocks[j] = blocks[i];
            j++;
        }
        i++;
    }
    new_blocks[j].x = -1;
    new_blocks[j].y = -1;
    new_blocks[j].id = -1;
    new_blocks[j].type = '\0';
    tmp = c->map->blocks;
    c->map->blocks = new_blocks;
    ft_free(tmp);
}

void add_block(float angle)
{
    int i;
    t_player *p = player();
    float x = 0;
    float y = 0;

    x = p->x - 0.5 + 2.5 * cos(angle);
    y = p->y - 0.5 + 2.5 * sin(angle);
    t_block *new_blocks;
    t_block *tmp;
    t_block *blocks = cube()->map->blocks;


    i = 0;
    while (blocks[i].x != -1)
        i++;
    new_blocks = ft_malloc(sizeof(t_block) * (i + 2));
    i = 0;
    while (blocks[i].x != -1)
    {
        new_blocks[i] = blocks[i];
        i++;
    }
    new_blocks[i].x = x;
    new_blocks[i].y = y;
    new_blocks[i].id = i;
    new_blocks[i].type = '2';
    new_blocks[i + 1].x = -1;
    new_blocks[i + 1].y = -1;
    new_blocks[i + 1].id = -1;
    new_blocks[i + 1].type = '\0';
    tmp = cube()->map->blocks;
    cube()->map->blocks = new_blocks;
    ft_free(tmp);
}

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

    float md = 2 +(-cos(angle * PI / 45));

    while(blocks[i].x != -1)
    {
        x = blocks[i].x;
        y = blocks[i].y;
        if((p_x - md <= x && x <= p_x + md) && (p_y - md <= y && y <= p_y + md))
            return i;
        i++;
    }
    return -1;
}

void open_door(float angle, int id)
{
    static bool opening = false;
    t_player *p = player();
    t_map *map = cube()->map;

    if(id == -1)
        return;
    if(!opening)
    {
        map->doors[id].save_y = map->doors[id].y;
        opening = true;
    }
    if(map->doors[id].y >= map->doors[id].save_y - 0.9)
        map->doors[id].y -= 0.05;
    else if(map->doors[id].y <= map->doors[id].save_y - 0.9)
    {
        printf("Door ID[%d] opened\n", id);
        p->opened = true;
    }
}

void close_door(float angle, int id)
{
    t_player *p = player();
    t_map *map = cube()->map;
    if(id == -1)
        return;
    static bool closing = false;
    if(!closing)
    {
        map->doors[id].save_y = map->doors[id].y + 0.9;
        closing = true;
    }
    if(map->doors[id].y <= map->doors[id].save_y)
        map->doors[id].y += 0.05;
    else if(map->doors[id].y >= map->doors[id].save_y)
    {
        printf("Door ID[%d] closed\n", id);
        p->opened = false;
    }
}


void catch_block(float angle)
{
    t_player *p = player();
    t_cube *c = cube();
    static int id;
    
    if(!c->map->blocks)
        return;
    if(!p->catched)
    {
        id = get_block_id(c->map->blocks, p->x, p->y, angle);
        p->catched = true;
    }
    if(id == -1)
    {
        p->catched = false;
        return;
    }
    c->map->blocks[id].x = p->x -0.5 + 2.5 * cos(angle);
    c->map->blocks[id].y = p->y -0.5 + 2.5 * sin(angle);
}
