/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:23:28 by escura            #+#    #+#             */
/*   Updated: 2024/06/21 18:39:40 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_pixel_from_image(int x, int y)
{
    t_texture *t = textures()->wall_north;

    x = x % t->width;
    y = y % t->height;

    if (x >= 0 && x < t->width && y >= 0 && y < t->height) {
        char *pixel = t->data + (y * t->size_line + x * (t->bpp / 8));
        return *(int *)pixel;
    }
    return 0;
}
