/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:44 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 14:09:40 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// Distance calculation function

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double	view_lane_distance(float x1, float y1, float angle)
{
	float	x2;
	float	y2;
	float	player_angle;
	float	raw_distance;
	double	adjusted_distance;

	x2 = 0;
	y2 = 0;
	player_angle = 0;
	raw_distance = 0;
	adjusted_distance = 0;
	x2 = player()->x_px;
	y2 = player()->y_px;
	player_angle = player()->angle;
	raw_distance = distance(x1, y1, x2, y2);
	adjusted_distance = raw_distance * cos(player_angle - angle);
	return (adjusted_distance);
}
