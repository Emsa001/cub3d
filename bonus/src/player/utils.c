/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:44 by escura            #+#    #+#             */
/*   Updated: 2024/09/19 19:26:33 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Distance calculation function
float distance(float x1, float y1, float x2, float y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// int view_lane_distance(float x1, float y1, float angle)
// {
//     float x2 = player()->x_px;
//     float y2 = player()->y_px;
    
//     float player_angle = player()->angle;
    
//     float raw_distance = distance(x1, y1, x2, y2);
//     float adjusted_distance = raw_distance * cos(player_angle - angle);

//     return adjusted_distance;
// }


void lane_distance(t_draw *draw)
{
    float x2 = player()->x_px;
    float y2 = player()->y_px;
    
    float player_angle = player()->angle;
    
    float raw_distance = distance(draw->first_x, draw->first_y, x2, y2);
    float adjusted_distance = raw_distance * cos(player_angle - draw->angle);
    draw->generator_dist = adjusted_distance;
    draw->height_top = (BLOCK_SIZE * HEIGHT) / adjusted_distance;

    raw_distance = distance(draw->last_x, draw->last_y, x2, y2);
    adjusted_distance = raw_distance * cos(player_angle - draw->angle);
    draw->height = (BLOCK_SIZE * HEIGHT) / adjusted_distance;

    raw_distance = distance(draw->x, draw->y, x2, y2);
    adjusted_distance = raw_distance * cos(player_angle - draw->angle);
    draw->dist = adjusted_distance;
    draw->wall_height = (BLOCK_SIZE * HEIGHT) / adjusted_distance;
}

int money()
{
    t_player *p = player();
    pthread_mutex_lock(&p->money_mutex);
    int money = p->money;
    pthread_mutex_unlock(&p->money_mutex);
    return money;
}

void add_money(int amount)
{
    t_player *p = player();

    pthread_mutex_lock(&p->money_mutex);
    p->money += amount;
    pthread_mutex_unlock(&p->money_mutex);
}

t_location *is_nerby(char cell)
{
    const t_player *p = player();
    const t_cube *c = cube();

    int x = (int)p->x_px / BLOCK_SIZE;
    int y = (int)p->y_px / BLOCK_SIZE;

    char nearby_cells[9];
    nearby_cells[0] = c->map->map[y][x];       // Current cell
    nearby_cells[1] = c->map->map[y-1][x];     // North
    nearby_cells[2] = c->map->map[y+1][x];     // South
    nearby_cells[3] = c->map->map[y][x-1];     // West
    nearby_cells[4] = c->map->map[y][x+1];     // East
    nearby_cells[5] = c->map->map[y-1][x-1];   // North-West
    nearby_cells[6] = c->map->map[y-1][x+1];   // North-East
    nearby_cells[7] = c->map->map[y+1][x-1];   // South-West
    nearby_cells[8] = c->map->map[y+1][x+1];   // South-East

    for(int i = 0; i < 9; i++) {
        if(nearby_cells[i] == cell) {
            t_location *loc = ft_malloc(sizeof(t_location));
            if(i == 0) {
                loc->x = x;
                loc->y = y;
            } else if(i == 1) {
                loc->x = x;
                loc->y = y-1;
            } else if(i == 2) {
                loc->x = x;
                loc->y = y+1;
            } else if(i == 3) {
                loc->x = x-1;
                loc->y = y;
            } else if(i == 4) {
                loc->x = x+1;
                loc->y = y;
            } else if(i == 5) {
                loc->x = x-1;
                loc->y = y-1;
            } else if(i == 6) {
                loc->x = x+1;
                loc->y = y-1;
            } else if(i == 7) {
                loc->x = x-1;
                loc->y = y+1;
            } else if(i == 8) {
                loc->x = x+1;
                loc->y = y+1;
            }
            return loc;
        }
    }

    return NULL;
}