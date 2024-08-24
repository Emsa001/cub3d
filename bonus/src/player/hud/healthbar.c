/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   healthbar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:09:25 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 14:39:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void hud_healthbar()
{
    t_textures *t = textures();
    t_player *p = player();
    t_render *r = render();
    int i = 0;
    int j = 0;
    int color = 0;

    put_image(t->healthhud, 0, 0);

    i = 0;
    while (i < p->health * 2)
    {
        j = 0;
        while (j < t->healthbar->height)
        {
            color = get_pixel_from_image(t->healthbar, i, j);
            if (color > 0){
                put_pixel(i, j, color, r);
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

        if(icon != NULL)
            put_image(icon, 0, 0);
    }
}