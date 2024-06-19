/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:44 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 20:36:50 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	distance(float x1, float y1)
{
	float	x2;
	float	y2;

	x2 = player()->x_px;
	y2 = player()->y_px;
	return (sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2)));
}


float view_lane_distance(float x1, float y1)
{
    float dist = distance(x1, y1);
    float x = player()->x_px - x1;
    // dist *= cosf(player()->angle * (PI / 180));

    return dist;
}