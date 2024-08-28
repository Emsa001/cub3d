/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:35:54 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 17:44:30 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_image(t_texture *img, int x, int y, float size)
{
    t_render *r = render();
    int i = 0;
    int j = 0;
    int color = 0;

    // Iterate over each pixel in the original image
    while (i < img->width)
    {
        j = 0;
        while (j < img->height)
        {
            // Get the color of the current pixel
            color = get_pixel_from_image(img, i, j);

            // Only draw if the color is valid (assuming non-negative values are valid)
            if (color >= 0)
            {
                // Draw the pixel in a scaled manner
                for (int dx = 0; dx < size; ++dx)
                {
                    for (int dy = 0; dy < size; ++dy)
                    {
                        put_pixel(x + i * size + dx, y + j * size + dy, color, r);
                    }
                }
            }

            j++;
        }
        i++;
    }
}
