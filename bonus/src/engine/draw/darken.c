/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:11:36 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/03 19:14:19 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	darken_color(int color, float dist)
{
	int	r;
	int	g;
	int	b;
	int	factor;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	factor = (int)((1.0f - dist) * 255);
	r = (r * factor) >> 8;
	g = (g * factor) >> 8;
	b = (b * factor) >> 8;
	return ((r << 16) | (g << 8) | b);
}

float	get_total_darken_factor(float factor, float wall_x, float wall_y,
		t_sprite *torches)
{
	int		i;
	float	total_darken_factor;
	float	torch_darken_factor;
	float	dist_to_torch;

	i = 0;
	total_darken_factor = 1.0f;
	while (torches[i].x != -1)
	{
		dist_to_torch = distance(wall_x, wall_y, torches[i].x, torches[i].y);
		torch_darken_factor = dist_to_torch / 2.0f;
		total_darken_factor = fminf(total_darken_factor,
				fminf(torch_darken_factor, factor));
		i++;
	}
	return (fminf(total_darken_factor, 1.0f));
}

int	darken_color_wall(int color, float factor, float wall_x, float wall_y)
{
	t_sprite	*torches;
	float		total_darken_factor;

	torches = cube()->map->facing;
	if (torches[0].x == -1)
		return (darken_color(color, factor));
	else
	{
		total_darken_factor = get_total_darken_factor(factor, wall_x, wall_y,
				torches);
		return (darken_color(color, total_darken_factor));
	}
}
