/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:35:54 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 14:52:20 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_image(t_texture *img, int x, int y)
{
    t_render *r = render();
    int i = 0;
    int j = 0;
    int color = 0;

    while (i < img->width)
    {
        j = 0;
        while (j < img->height)
        {
            color = get_pixel_from_image(img, i, j);
            if(color >= 0)
                put_pixel(x + i, y + j, color, r);
            j++;
        }
        i++;
    }
}