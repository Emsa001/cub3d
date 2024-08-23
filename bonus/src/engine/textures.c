/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:23:28 by escura            #+#    #+#             */
/*   Updated: 2024/08/23 14:42:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_scene_pixel(int x, int y)
{
    t_render *r = render();

    x = x % WIDTH;
    y = y % HEIGHT;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        char *pixel = r->data + (y * r->size_line + x * (r->bpp / 8));
        return *(int *)pixel;
    }
    return 0;
}

int get_pixel_from_image(t_texture *t, int x, int y)
{
    x = x % t->width;
    y = y % t->height;

    if (x >= 0 && x < t->width && y >= 0 && y < t->height) {
        char *pixel = t->data + (y * t->size_line + x * (t->bpp / 8));
        return *(int *)pixel;
    }
    return 0;
}

void resize_texture(const t_texture *src, t_texture *dst, int new_width, int new_height)
{
    int x_ratio = (int)((src->width << 16) / new_width) + 1;
    int y_ratio = (int)((src->height << 16) / new_height) + 1;
    int x2, y2;
    for (int i = 0; i < new_height; i++)
    {
        for (int j = 0; j < new_width; j++)
        {
            x2 = ((j * x_ratio) >> 16);
            y2 = ((i * y_ratio) >> 16);
            int src_pos = (y2 * src->size_line) + (x2 * (src->bpp / 8));
            int dst_pos = (i * dst->size_line) + (j * (dst->bpp / 8));
            dst->data[dst_pos] = src->data[src_pos];
            dst->data[dst_pos + 1] = src->data[src_pos + 1];
            dst->data[dst_pos + 2] = src->data[src_pos + 2];
            dst->data[dst_pos + 3] = src->data[src_pos + 3]; // Assuming 4 bytes per pixel
        }
    }
}
