/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:35:54 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 23:28:13 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_scaled(int x, int y, int color, float size)
{
	int	dx;
	int	dy;

	dx = 0;
	while (dx < size)
	{
		dy = 0;
		while (dy < size)
		{
			put_pixel(x + dx, y + dy, color, render());
			dy++;
		}
		dx++;
	}
}

void	put_image_pixels(t_texture *img, int x, int y, float size)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < img->height)
		{
			color = get_pixel_from_image(img, i, j);
			if (color && color > 0)
				put_pixel_scaled(x + i * size, y + j * size, color, size);
			j++;
		}
		i++;
	}
}

void	put_image(t_texture *img, int x, int y, float size)
{
	const t_render	*r = render();

	if (!r->img_ptr || !img)
		return ;
	put_image_pixels(img, x, y, size);
}
