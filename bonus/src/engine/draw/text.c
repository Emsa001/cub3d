/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:34:36 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 16:56:29 by escura           ###   ########.fr       */
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

    // Create a buffer to hold the character pixel data
    int char_pixel_data[95][32 * 32];

    // Load character pixel data from the font texture
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

    // Iterate over each character in the string
    while (*str)
    {
        char ch = *str++;
        if (ch < ' ' || ch > '~') continue; 

        int char_index = ch - ' ';
        int *pixels = char_pixel_data[char_index];

        // Render each character at the specified location and size
        for (int i = 0; i < char_width; ++i)
        {
            for (int j = 0; j < char_height; ++j)
            {
                int pixel_color = pixels[i + j * char_width];
                if (pixel_color > 0)  // Assuming non-zero values are valid pixels
                {
                    // Draw the pixel with scaling
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

        // Move to the next character position
        x += char_width * size;
    }
}
