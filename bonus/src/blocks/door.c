/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:41 by btvildia          #+#    #+#             */
/*   Updated: 2024/07/21 13:14:12 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int block_count(t_map *map_info, char c)
{
    int i;
    int j;
    int count;

    i = 0;
    j = 0;
    count = 0;

    if(c == '2')
    {
        if(map_info->blocks == NULL)
            return (0);
        while(map_info->blocks[count].x != -1)
            count++;
    }
    else
    {
        while (map_info->map[i] != NULL)
        {
            j = 0;
            while (map_info->map[i][j] != '\0')
            {
                if (map_info->map[i][j] == c)
                    count++;
                j++;
            }
            i++;
        }
    }
    return (count);
}

t_block    *init_block(t_map *map_info , char c)
{
    t_block    *blocks;
    int        i;
    int        j;
    int        k;
    
    map_info->blocks = NULL;
    int count = block_count(map_info, c);
    blocks = ft_malloc(sizeof(t_block) * (count + 1));
    i = 0;
    j = 0;
    k = 0;
    while (map_info->map[i] != NULL)
    {
        j = 0;
        while (map_info->map[i][j] != '\0')
        {
            if (map_info->map[i][j] == c)
            {
                blocks[k].x = j;
                blocks[k].y = i;
                blocks[k].s_x = j;
                blocks[k].s_y = i;
                blocks[k].id = k;
                blocks[k].type = c;
                k++;
            }
            j++;
        }
        i++;
    }
    blocks[k].x = -1;
    blocks[k].y = -1;
    blocks[k].id = -1;
    blocks[k].s_x = -1;
    blocks[k].s_y = -1;
    blocks[k].type = '\0';
    return (blocks);
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
        map->doors[id].s_y = map->doors[id].y;
        opening = true;
    }
    if(map->doors[id].y >= map->doors[id].s_y - 0.9)
        map->doors[id].y -= 0.05;
    else if(map->doors[id].y <= map->doors[id].s_y - 0.9)
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
        map->doors[id].s_y = map->doors[id].y + 0.9;
        closing = true;
    }
    if(map->doors[id].y <= map->doors[id].s_y)
        map->doors[id].y += 0.05;
    else if(map->doors[id].y >= map->doors[id].s_y)
    {
        printf("Door ID[%d] closed\n", id);
        p->opened = false;
    }
}