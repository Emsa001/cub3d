/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   healthbar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:09:25 by escura            #+#    #+#             */
/*   Updated: 2024/08/23 22:22:31 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_healthbar()
{
    t_textures *t = textures();
    t_player *p = player();
    t_render *r = render();
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;
    int color = 0;

    while (i < t->healthhud->width)
    {
        j = 0;
        while (j < t->healthhud->height)
        {
            color = get_pixel_from_image(t->healthhud, i, j);
            if (color > 0){
                put_pixel(x + i, y + j, color, r);
            }
            j++;
        }
        i++;
    }

    i = 0;
    while (i < p->health * 2)
    {
        j = 0;
        while (j < t->healthbar->height)
        {
            color = get_pixel_from_image(t->healthbar, i, j);
            if (color > 0){
                put_pixel(x + i, y + j, color, r);
            }
            j++;
        }
        i++;
    }

    if(p->health > 0){
        t_texture *icon = NULL;
    
        if(p->health >= 90){
            icon = t->healthIcon[0];
        } else if(p->health >= 75){
            icon = t->healthIcon[1];
        } else if(p->health >= 50){
            icon = t->healthIcon[2];
        } else if(p->health >= 25){
            icon = t->healthIcon[3];
        }

        if(icon == NULL){
            return;
        }

        i = 0;
        while (i < icon->width)
        {
            j = 0;
            while (j < icon->height)
            {
                color = get_pixel_from_image(icon, i, j);
                if (color > 0){
                    put_pixel(x + i, y + j, color, r);
                }
                j++;
            }
            i++;
        }
    }

}