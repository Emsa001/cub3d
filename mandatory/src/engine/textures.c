/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:23:28 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 14:10:52 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_pixel_from_image(int x, int y, int side)
{
	t_texture	*t;
	char		*pixel;

	if (side == 1)
		t = textures()->wall_north;
	else if (side == 2)
		t = textures()->wall_south;
	else if (side == 3)
		t = textures()->wall_east;
	else if (side == 4)
		t = textures()->wall_west;
	else
		return (0);
	x = x % t->width;
	y = y % t->height;
	if (x >= 0 && x < t->width && y >= 0 && y < t->height)
	{
		pixel = t->data + (y * t->size_line + x * (t->bpp / 8));
		return (*(int *)pixel);
	}
	return (0);
}
