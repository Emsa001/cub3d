/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:12:05 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/01 12:40:35 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_top_and_bottom(int x, int y)
{
	int	i;
	int	j;

	i = CORNER;
	j = CORNER;
	while (i < MINIMAP_PIXEL_WIDTH - CORNER)
	{
		while (j < FRAME_WIDTH)
		{
			put_pixel(x + i, y + j - FRAME_WIDTH, FRAME_COLOR, render());
			put_pixel(x + i, y + MINIMAP_PIXEL_HEIGHT - 1 - j + FRAME_WIDTH,
				FRAME_COLOR, render());
			j++;
		}
		j = 0;
		i++;
	}
}

static void	draw_left_and_right(int x, int y)
{
	int	i;
	int	j;

	i = CORNER;
	j = CORNER;
	while (j < MINIMAP_PIXEL_HEIGHT - CORNER)
	{
		while (i < FRAME_WIDTH)
		{
			put_pixel(x + i - FRAME_WIDTH, y + j, FRAME_COLOR, render());
			put_pixel(x + MINIMAP_PIXEL_WIDTH - 1 - i + FRAME_WIDTH, y + j,
				FRAME_COLOR, render());
			i++;
		}
		i = 0;
		j++;
	}
}

void	draw_minimap_square(int x, int y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	draw_top_and_bottom(x, y);
	draw_left_and_right(x, y);
	while (i < MINIMAP_PIXEL_WIDTH)
	{
		j = 0;
		while (j < MINIMAP_PIXEL_HEIGHT)
		{
			put_pixel(x + i, y + j, MINIMAP_COLOR, render());
			j++;
		}
		i++;
	}
}
