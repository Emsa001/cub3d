/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chest.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:47:24 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/08 19:53:02 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void draw_chest(t_draw draw, ThreadParams *params, int tex_x, float angle)
{
    int color = params->color;
    float tex_y = 0;
    int dist = draw.chest_dist;
    float step = (float)(T_SIZE * 2) / draw.height_top;
    const t_player *p = params->player;
    const t_render *r = params->render;

    int start_y = (p->z - 0.4) * draw.height_top + vert_offset(p);
    int end_y = start_y + draw.height_top * 0.4;

    if(end_y > HEIGHT)
        end_y = HEIGHT;

    while (start_y < end_y)
    {
        if(!p->vision && dist > 450)
            break;
        color = get_pixel_from_image(params->textures->chest, tex_x * 2, tex_y);
        if(!p->vision)
            color = darken_color(color, (float)dist / 450);

        put_pixel(draw.start_x, start_y, color, r);

        tex_y += step;
        start_y++;
    }
}

void draw_chest_top(t_draw draw, ThreadParams *params, float angle)
{
    const t_cube *c = params->cube;
    const t_player *p = params->player;
    const t_textures *texs = params->textures;
    float head_x = 0;
    float head_y = 0;
    
    float cosangle = cos(angle);
    float sinangle = sin(angle);
    int color = 123;
    int start_y = HEIGHT / 2 + ((p->z - 0.4) * draw.height);
    int end_y = (HEIGHT / 2 + ((p->z - 0.4) * draw.height_top)) + draw.height_top * 0.01;

    float current_dist = 0;

    t_texture *head = texs->wall_south;

    if(end_y > HEIGHT)
        end_y = HEIGHT;

    while(start_y < end_y)
    {
        current_dist = view_current_distance(p, start_y, angle, 0.4);
        if(!p->vision && current_dist > 7)
            break;
        
        color = get_pixel_from_image(params->textures->chest_top, head_x * (T_SIZE * 2), head_y * (T_SIZE * 2));

        if(!p->vision)
            color = darken_color(color, (float)current_dist / 7);
        
        head_x = (p->x) + current_dist * cosangle;
        head_y = (p->y) + current_dist * sinangle;
        put_pixel(draw.start_x, start_y, color, params->render);

        start_y++;
    }
}
