/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:51:28 by escura            #+#    #+#             */
/*   Updated: 2024/09/29 18:09:15 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_triangle(int size, int x, int y, int color)
{
	int	i;
	int	start_x;
	int	end_x;
	int	height;
	int	j;

	i = 0;
	start_x = 0;
	end_x = 0;
	height = 0;
	j = 0;
	y = y - size / 2;
	height = (int)(size * sin((80) * PI / 180.0));
	while (i < height)
	{
		start_x = x - (i * size) / height / 2;
		end_x = x + (i * size) / height / 2;
		j = start_x;
		while (j <= end_x)
		{
			put_pixel(j, y + i, color, render());
			j++;
		}
		i++;
	}
}

void	draw_player(int x, int y)
{
	draw_triangle(MINIMAP_PLAYER_SIZE + 8, x, y, 0);
	draw_triangle(MINIMAP_PLAYER_SIZE, x, y + 1, MINIMAP_PLAYER_COLOR);
}
