/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:44 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 18:38:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Distance calculation function
float distance(float x1, float y1, float x2, float y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int view_lane_distance(float x1, float y1, float angle)
{
    float x2 = player()->x_px;
    float y2 = player()->y_px;
    
    float player_angle = player()->angle;
    
    float raw_distance = distance(x1, y1, x2, y2);
    int adjusted_distance = raw_distance * cos(player_angle - angle);

    return adjusted_distance;
}
