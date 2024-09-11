/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:03:04 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 14:25:14 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int vert_offset(t_player *p)
{
    return (p->z_dir) * HEIGHT;
}

t_texture *get_wall_side(int side, t_textures *texs)
{
    t_texture *t = NULL;
    
    if (side == 1)
        t = texs->wall_north;
    else if (side == 2)
        t = texs->wall_south;
    else if (side == 3)
        t = texs->wall_east;
    else if (side == 4)
        t = texs->wall_west;
    else if (side == 5)
        t = texs->door;
    else if (side == 6)
        t = texs->wall_west;
    else if (side == 7)
        t = texs->wall_south;
    else
        return NULL;
    return t;
}

int darken_color(int color, float ratio)
{
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;

    int factor = (int)((1.0f - ratio) * 255);

    r = (r * factor) >> 8;
    g = (g * factor) >> 8;
    b = (b * factor) >> 8;

    return (r << 16) | (g << 8) | b;
}

float view_current_distance(t_player *p, int start_y, float angle, float z)
{
    float current_dist = (p->z - z) * HEIGHT / (start_y - HEIGHT / 2);
    return current_dist / cos(angle - p->angle);
}

void draw_floor(int height, int start_x, ThreadParams *params, float angle)
{
    const t_cube *c = params->cube;
    const t_player *p = params->player;
    const t_textures *texs = params->textures;
    int start_y = HEIGHT;
    float floor_x = 0;
    float floor_y = 0;
    
    float cosangle = cos(angle);
    float sinangle = sin(angle);
    int color = 0;

    float current_dist = 0;

    t_texture *floor = texs->floor;

    while (start_y > HEIGHT / 2 + (p->z * height) )
    {
        current_dist = view_current_distance(p, start_y, angle, 0);
           
        if(!p->vision && current_dist > 7)
            break;
        
        floor_x = (p->x) + current_dist * cosangle;
        floor_y = (p->y) + current_dist * sinangle;

        color = get_pixel_from_image(floor, floor_x * T_SIZE, floor_y * T_SIZE);
        if(!p->vision)
            color = darken_color(color, (float)current_dist / 7);

        put_pixel(start_x, start_y, color, params->render);

        start_y--;
    }
}

void draw_sky(int height, int start_x, ThreadParams *params, float angle)
{
    const t_cube *c = params->cube;
    const t_player *p = params->player;
    const t_textures *texs = params->textures;
    int start_y = 0;
    float sky_x = 0;
    float sky_y = 0;
    
    float cosangle = cos(angle);
    float sinangle = sin(angle);
    int color = 0;

    float current_dist = 0;

    t_texture *sky = texs->sky;

    while (start_y < ((p->z * height) + HEIGHT / 2) - height)
    {
        current_dist = view_current_distance(p, start_y, angle, 1);

        if(!p->vision && current_dist > 7)  
            break;
            
        sky_x = (p->x) + current_dist * cosangle;
        sky_y = (p->y) + current_dist * sinangle;

        color = get_pixel_from_image(sky, sky_x * T_SIZE, sky_y * T_SIZE);

        if(!p->vision)
            color = darken_color(color, (float)current_dist / 7);

        put_pixel(start_x, start_y, color, params->render);

        start_y++;
    }
}


void draw_wall(t_draw draw, ThreadParams *params)
{
    int color = params->color;
    float tex_y = 0;
    float step = (float)T_SIZE / draw.wall_height;
    const t_cube *c = params->cube;
    const t_player *p = params->player;
    const t_render *r = params->render;
    const t_textures *texs = params->textures;

    bool catched = p->catch && draw.side == 6;  // Use side instead of r->side
    t_texture *wall_side = get_wall_side(draw.side, texs);  // Use side instead of r->side
    
    if (!wall_side || draw.side == 7)
        return;

    int start_y = (p->z - 1) * draw.wall_height + vert_offset(p);
    int end_y = start_y + draw.wall_height;

    if (end_y > HEIGHT)
        end_y = HEIGHT; 
    if(start_y < 0)
    {
        tex_y = -start_y * step;
        start_y = 0;
    }

    while (start_y < end_y)
    {
        if(!p->vision && draw.dist > 450)
            break;
        if (catched)
            color = 255;
        else
        {
            color = get_pixel_from_image(wall_side, draw.tex_x, tex_y);
            if(!p->vision)
                color = darken_color(color, (float)draw.dist / 450);
        }

        put_pixel(draw.start_x, start_y, color, r);

        tex_y += step;
        start_y++;
    }
}