/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:35:54 by escura            #+#    #+#             */
/*   Updated: 2024/09/07 16:06:02 by escura           ###   ########.fr       */
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
            color = get_pixel_from_image(img, i, j);

            if (color >= 0)
            {
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

void change_image_color(t_texture *img, int color)
{
    int i = 0;
    int j = 0;

    while (i < img->width)
    {
        j = 0;
        while (j < img->height)
        {
            int index = j * img->size_line + i * img->bpp / 8;
            img->data[index] = color & 0xFF;              // Blue component
            img->data[index + 1] = (color >> 8) & 0xFF;   // Green component
            img->data[index + 2] = (color >> 16) & 0xFF;  // Red component
            j++;
        }
        i++;
    }
}