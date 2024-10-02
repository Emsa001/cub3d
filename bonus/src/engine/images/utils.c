/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:17:53 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 23:19:45 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_image_color(t_texture *img, int color)
{
	int	i;
	int	index;
	int	j;

	if (!img)
		return ;
	i = 0;
	while (i < img->width)
	{
		index = i * img->bpp / 8;
		j = 0;
		while (j < img->height)
		{
			img->data[index] = color & 0xFF;
			img->data[index + 1] = (color >> 8) & 0xFF;
			img->data[index + 2] = (color >> 16) & 0xFF;
			index += img->size_line;
			++j;
		}
		++i;
	}
}
