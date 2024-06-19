/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:44 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 20:04:06 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float distance(float x1, float y1)
{
    float x2 = player()->x_px;
    float y2 = player()->y_px;

    return sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
}


float view_lane_distance(float x1, float y1)
{
    float dist = distance(x1, y1);
    float x = player()->x_px - x1;
    // dist *= cosf(player()->angle * (PI / 180));

    return dist;
}