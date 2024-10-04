/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:12:05 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/04 20:04:11 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_top_and_bottom(int x, int y)
{
	int	i;
	int	j;

	i = CORNER;
	j = CORNER;
	while (i < WIDTH / 6 - CORNER)
	{
		while (j < FRAME_WIDTH)
		{
			put_pixel(x + i, y + j - FRAME_WIDTH, FRAME_COLOR, render());
			put_pixel(x + i, y + WIDTH / 8 - 1 - j + FRAME_WIDTH,
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
	while (j < WIDTH / 8 - CORNER)
	{
		while (i < FRAME_WIDTH)
		{
			put_pixel(x + i - FRAME_WIDTH, y + j, FRAME_COLOR, render());
			put_pixel(x + WIDTH / 6 - 1 - i + FRAME_WIDTH, y + j,
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
	while (i < WIDTH / 6)
	{
		j = 0;
		while (j < WIDTH / 8)
		{
			put_pixel(x + i, y + j, MINIMAP_COLOR, render());
			j++;
		}
		i++;
	}
}
