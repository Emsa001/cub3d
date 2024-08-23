/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:03:04 by escura            #+#    #+#             */
/*   Updated: 2024/08/23 16:59:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int vert_offset(t_player *p)
{
    return (p->z_dir) * HEIGHT;
}

static t_texture *get_wall_side(int side, t_textures *texs)
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
        t = texs->wall_west;\
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

float view_current_distance(t_player *p, int start_y, float angle)
{
    float current_dist = p->z * HEIGHT / (start_y - HEIGHT / 2);
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
        
        current_dist = view_current_distance(p, start_y, angle);
           
        if(current_dist > 7)
            break;
        
        floor_x = (p->x) + current_dist * cosangle;
        floor_y = (p->y) + current_dist * sinangle;

        color = get_pixel_from_image(floor, floor_x * T_SIZE, floor_y * T_SIZE);
       
        color = darken_color(color, (float)current_dist / 7);

        put_pixel(start_x, start_y, color);

        start_y--;
    }
}

void draw_wall(int height, int start_x, ThreadParams *params, int dist)
{
    int color;
    float tex_y = 0;
    float step = (float)T_SIZE / height;
    const t_cube *c = params->cube;
    const t_player *p = params->player;
    const t_render *r = params->render;
    const t_textures *texs = params->textures;
    bool catched = p->catch && r->side == 6;


    t_texture *wall_side = get_wall_side(r->side, texs);
    if (!wall_side)
        return;
    int start_y = (p->z - 1) * height + vert_offset(p);
    int end_y = start_y + height;

    
    // if (height > HEIGHT)
    // {
    //     tex_y = (-p->z + 1) * (height) * step;
    //     height = HEIGHT;
    // }

    // if (start_y < 0)
    //     start_y = 0;
    if (end_y > HEIGHT)
        end_y = HEIGHT;
        
    while(start_y < end_y && dist < 450)
    {
        if (catched)
            color = 255;
        else
        {
            color = get_pixel_from_image(wall_side, c->tex_x, tex_y);
            color = darken_color(color, (float)dist / 450);
        }
        put_pixel(start_x, start_y, color);
        tex_y += step;
        start_y++;
    }   
}

