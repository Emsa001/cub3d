/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:34:36 by escura            #+#    #+#             */
/*   Updated: 2024/09/07 19:51:29 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// https://stmn.itch.io/font2bitmap
void write_string(char *str, int x, int y, int color, float size)
{
    t_texture *font = textures()->font;
    t_render *r = render();

    const int char_width = 32;
    const int char_height = 32; 
    const int chars_per_row = 16; 

    int char_pixel_data[95][32 * 32];

    for (int index = 0; index < 95; ++index)
    {
        int row = index / chars_per_row;
        int col = index % chars_per_row;
        int src_x = col * char_width;
        int src_y = row * char_height;
        
        for (int i = 0; i < char_width; ++i)
        {
            for (int j = 0; j < char_height; ++j)
            {
                int pixel_color = get_pixel_from_image(font, src_x + i, src_y + j);
                char_pixel_data[index][i + j * char_width] = pixel_color;
            }
        }
    }

    while (*str)
    {
        char ch = *str++;
        if (ch && ch < ' ' || ch > '~') continue; 

        int char_index = ch - ' ';
        int *pixels = char_pixel_data[char_index];

        for (int i = 0; i < char_width; ++i)
        {
            for (int j = 0; j < char_height; ++j)
            {
                int pixel_color = pixels[i + j * char_width];
                if (pixel_color > 0) 
                {
                    for (int dx = 0; dx < size; ++dx)
                    {
                        for (int dy = 0; dy < size; ++dy)
                        {
                            put_pixel(x + i * size + dx, y + j * size + dy, color, r);
                        }
                    }
                }
            }
        }

        x += char_width * size;
    }
}
