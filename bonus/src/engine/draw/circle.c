/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:43:30 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 17:52:51 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(int center_x, int center_y, int radius, int color)
{
	t_render *r = render();

	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		// Fill the circle by drawing horizontal lines
		for (int i = center_x - x; i <= center_x + x; i++)
		{
			put_pixel(i, center_y + y, color, r);
			put_pixel(i, center_y - y, color, r);
		}

		for (int i = center_x - y; i <= center_x + y; i++)
		{
			put_pixel(i, center_y + x, color, r);
			put_pixel(i, center_y - x, color, r);
		}

		y++;
		err += 2 * y + 1;

		if (err > x * 2)
		{
			x--;
			err -= 2 * x + 1;
		}
	}
}