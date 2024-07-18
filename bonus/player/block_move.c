/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:53:45 by btvildia          #+#    #+#             */
/*   Updated: 2024/07/18 14:24:16 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_block *get_all_possible_blocks(int x, int y)
{
    t_block *possible = ft_malloc(sizeof(t_block) * 12);
    possible[0].x = x + 2;
    possible[0].y = y;
    possible[1].x = x + 2;
    possible[1].y = y + 1;
    possible[2].x = x + 1;
    possible[2].y = y + 2;
    possible[3].x = x;
    possible[3].y = y + 2;
    possible[4].x = x - 1;
    possible[4].y = y + 2;
    possible[5].x = x - 2;
    possible[5].y = y + 1;
    possible[6].x = x - 2;
    possible[6].y = y;
    possible[7].x = x - 2;
    possible[7].y = y - 1;
    possible[8].x = x - 1;
    possible[8].y = y - 2;
    possible[9].x = x;
    possible[9].y = y - 2;
    possible[10].x = x + 1;
    possible[10].y = y - 2;
    possible[11].x = x + 2;
    possible[11].y = y - 1;
    return possible;
}

void get_currect_block(t_block *possible, float ray_angle, int *x, int *y)
{
    if(ray_angle >= 345 || ray_angle < 15)
    {
        *x = possible[0].x;
        *y = possible[0].y;
    }
    else if(ray_angle >= 15 && ray_angle < 45)
    {
        *x = possible[1].x;
        *y = possible[1].y;
    }
    else if(ray_angle >= 45 && ray_angle < 75)
    {
        *x = possible[2].x;
        *y = possible[2].y;
    }
    else if(ray_angle >= 75 && ray_angle < 105)
    {
        *x = possible[3].x;
        *y = possible[3].y;
    }
    else if(ray_angle >= 105 && ray_angle < 135)
    {
        *x = possible[4].x;
        *y = possible[4].y;
    }
    else if(ray_angle >= 135 && ray_angle < 165)
    {
        *x = possible[5].x;
        *y = possible[5].y;
    }
    else if(ray_angle >= 165 && ray_angle < 195)
    {
        *x = possible[6].x;
        *y = possible[6].y;
    }
    else if(ray_angle >= 195 && ray_angle < 225)
    {
        *x = possible[7].x;
        *y = possible[7].y;
    }
    else if(ray_angle >= 225 && ray_angle < 255)
    {
        *x = possible[8].x;
        *y = possible[8].y;
    }
    else if(ray_angle >= 255 && ray_angle < 285)
    {
        *x = possible[9].x;
        *y = possible[9].y;
    }
    else if(ray_angle >= 285 && ray_angle < 315)
    {
        *x = possible[10].x;
        *y = possible[10].y;
    }
    else if(ray_angle >= 315 && ray_angle < 345)
    {
        *x = possible[11].x;
        *y = possible[11].y;
    }
}

void spawn_block(float angle, int i)
{
    t_player *p = player();
    t_cube *c = cube();
    t_map *map = c->map;
    t_block *possible;

    
    int x = 0;
    int y = 0;

    angle = angle * (180 / PI);
    
    possible = get_all_possible_blocks(p->x, p->y);

    get_currect_block(possible, angle, &x, &y);
    
    if(i == 1)
    {
        if(map->map[y][x] == '0')
        {
            map->map[y][x] = '2';
            c->map->blocks = init_block(map, '2');
        }
        else
            printf("Can't spawn block here \n");
    }
    else
    {
        if(map->map[y][x] == '2')
        {
            map->map[y][x] = '0';
            c->map->blocks = init_block(map, '2');
        }
        else
            printf("Can't remove block here \n");
    }
    ft_free(possible);
}

int get_block_id(t_block *blocks, float px, float py, char angle)
{
    t_cube *c = cube();
    float x = 0;
    float y = 0;
    int i = 0;

    while(blocks[i].x != -1)
    {
        x = blocks[i].x * BLOCK_SIZE;
        y = blocks[i].y * BLOCK_SIZE;
        if(px >= x && px <= x + BLOCK_SIZE && py >= y && py <= y + BLOCK_SIZE)
            return i;
        i++;
    }

    return -1;
}

void catch_block(float angle)
{
    t_player *p = player();
    t_cube *c = cube();
    
    if(!c->map->blocks)
        return;

    
    int id = 0;
    // id = get_block_id(c->map->blocks, p->x, p->y, angle);
    
    c->map->blocks[id].x = p->x -0.5 + 2.5 * cos(angle);
    c->map->blocks[id].y = p->y -0.5 + 2.5 * sin(angle);
}
