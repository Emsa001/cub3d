/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:44 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 19:04:22 by btvildia         ###   ########.fr       */
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

float	view_lane_distance(float x1, float y1)
{
	float x2 = player()->x_px;
	float y2 = player()->y_px;

	float angle = player()->angle;
	float angle2 = atan2f(y1 - y2, x1 - x2);
	float diff = angle - angle2;

	if (diff < -PI)
		diff += 2 * PI;
	if (diff > PI)
		diff -= 2 * PI;

	return (distance(x1, y1) * cosf(diff));
}