/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:51:28 by escura            #+#    #+#             */
/*   Updated: 2024/07/22 19:00:53 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* it detects colors, I believe there is better way to do it */
static void minimap_draw_fov(float angle)
{
    float x = minimap_center_x();
    float y = minimap_center_y();
    int col = 0;
    int i = 0;
    
    while (i < 100 && col <= 20)
    {
        x += cos(angle);
        y += sin(angle);

        if(get_scene_pixel((int)x, (int)y) == MINIMAP_COLOR){
            if(i % 4 == 0)
                put_pixel((int)x, (int)y, 0xa1a1aa);
        }else
            col++;

        i++;
    }
}

void minimap_draw_player()
{
    const t_player *p = player();
    float angle = p->angle;

    float fovInRadians = p->fov * PI / 180;
    float halfFovInRadians = fovInRadians / 2.0;
    float angleOffset = angle - halfFovInRadians;

    draw_circle(minimap_center_x(), minimap_center_y(), PLAYER_SIZE, PLAYER_DOT_COLOR);

    int i = 0;
    while (i < WIDTH) 
    {
        float fraction = (float)i / WIDTH;
        float rayAngle = angleOffset + fraction * fovInRadians;
        minimap_draw_fov(rayAngle);
        i += 170 - p->fov;
    }
}