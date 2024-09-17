/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:44 by escura            #+#    #+#             */
/*   Updated: 2024/09/17 16:58:05 by escura           ###   ########.fr       */
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

    raw_distance = distance(draw->sprite_x, draw->sprite_y, x2, y2);
    adjusted_distance = raw_distance * cos(player_angle - draw->angle);
    draw->sprite_dist = adjusted_distance;
    draw->sprite_height = (BLOCK_SIZE * HEIGHT) / adjusted_distance;
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
