/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:44 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 21:04:43 by escura           ###   ########.fr       */
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
    float dx = player()->x_px;
    float dy = player()->y_px;

    float meet_angle = atan2f(y1 - dy, x1 - dx);
    float player_directrion = atan2f(player()->y_dir, player()->x_dir);

    printf("meet_angle: %f\n", meet_angle);

    float dist = distance(x1, y1) * cosf(player_directrion - meet_angle);

    return dist;
}