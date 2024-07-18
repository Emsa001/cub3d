/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:41 by btvildia          #+#    #+#             */
/*   Updated: 2024/07/18 18:38:31 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void open_door(void)
{
    t_player *p = player();
    t_cube *c = cube();
    t_block *doors = c->map->doors;
    static int open;
    if(c->map->doors == NULL)
        return;
    
    if(doors[0].y >= doors[0].first_y - 0.9 && doors[0].y == doors[0].first_y)
            open = 1;
    else if(doors[0].y <= doors[0].first_y && doors[0].y <= doors[0].first_y - 0.9)
            open = 0;

    if(open == 1)
        doors[0].y = doors[0].y - 0.05;
    else
        doors[0].y = doors[0].y + 0.05;

    p->interact = false;
}

void    print_block_info(t_block *blocks)
{
    int i;

    i = 0;
    printf("Block info:\n");
    while (blocks[i].x != -1)
    {
        printf("Door %d: x = %f, y = %f\n", blocks[i].id, blocks[i].x, blocks[i].y);
        i++;
    }
}

int block_count(t_map *map_info, char c)
{
    int i;
    int j;
    int count;

    i = 0;
    j = 0;
    count = 0;
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
    return (count);
}

void add_block(float x, float y)
{
    int i;
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
    new_blocks[i].first_x = x;
    new_blocks[i].first_y = y;
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

t_block    *init_block(t_map *map_info , char c)
{
    t_block    *blocks;
    int        i;
    int        j;
    int        k;

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
                blocks[k].first_x = j;
                blocks[k].first_y = i;
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
    blocks[k].type = '\0';
    return (blocks);
}
