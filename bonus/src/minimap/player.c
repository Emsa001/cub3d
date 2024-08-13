/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:51:28 by escura            #+#    #+#             */
/*   Updated: 2024/08/13 11:48:39 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* it detects colors, I believe there is better way to do it */
static void minimap_draw_fov(float angle)
{
    t_render *r = render();
    float x = minimap_center_x();
    float y = minimap_center_y();
    int col = 0;
    int i = 0;
    
    const double cos_angle = cos(angle);
    const double sin_angle = sin(angle);

    while (i < 100 && col <= 3)
    {
        x += 6 * cos_angle;
        y += 6 * sin_angle;

        if(get_scene_pixel((int)x, (int)y) != MINIMAP_COLOR)
            col++;

        put_pixel((int)x, (int)y, 0xa1a1aa);
        i += 6;
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
        i += (170 - p->fov);
    }
}