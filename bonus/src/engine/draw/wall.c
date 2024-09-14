/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:03:04 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 16:13:20 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int vert_offset(const t_player *p)
{
    return (p->z_dir) * HEIGHT;
}

t_texture *get_wall_side(int side, const t_textures *texs, int n)
{
    t_texture *t = NULL;

    
    if (side == 1)
        t = texs->wall_north[n];
    else if (side == 2)
        t = texs->wall_south[n];
    else if (side == 3)
        t = texs->wall_east[n];
    else if (side == 4)
        t = texs->wall_west[n];
    else if (side == 5)
        t = texs->door;
    else if (side == 6)
        t = texs->wall_west[n];
    else if (side == 7)
        t = texs->wall_south[n];
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

float view_current_distance(const t_player *p, int start_y, float angle)
{
    float z = 1;
    if(start_y >= HEIGHT / 2)
        z = 0;

    float current_dist = (p->z - z) * HEIGHT / (start_y - HEIGHT / 2);
    return current_dist / cos(angle - p->angle);
}

t_texture* get_texture(int start_y, int height, const t_player *p, const t_textures *texs)
{
    if (start_y > HEIGHT / 2 + (p->z * height))
    {
        return texs->floor[player()->level];
    }
    else if (start_y < ((p->z * height) + HEIGHT / 2) - height)
    {
        return texs->ceiling[player()->level];
    }
    return NULL;
}

int get_texture_color(t_texture *tex, float dist, float cosangle, float sinangle)
{
    float tex_x = player()->x + dist * cosangle;
    float tex_y = player()->y + dist * sinangle;
    int color = get_pixel_from_image(tex, tex_x * T_SIZE, tex_y * T_SIZE);
    return darken_color(color, dist / 7);
}

void draw_floor_and_ceiling(int height, int start_x, ThreadParams *params, float angle)
{
    const t_player *p = params->player;
    const t_textures *texs = params->textures;
    float cosangle = cos(angle);
    float sinangle = sin(angle);
    int start_y = HEIGHT;
    int color = 0;
    
    while (start_y > 0)
    {
        t_texture *tex = get_texture(start_y, height, p, texs);
        float current_dist = view_current_distance(p, start_y, angle);
        if (!tex || current_dist > 7)
        {
            start_y--;
             continue;
        }
        color =  get_texture_color(tex, current_dist, cosangle, sinangle);
        put_pixel(start_x, start_y, color, params->render);
        start_y--;
    }
}

void draw_wall(t_draw draw, ThreadParams *params)
{
    int color = params->color;
    float tex_y = 0;
    float step = (float)T_SIZE / draw.wall_height;
    const t_cube *c = params->cube;
    const t_player *p = params->player;
    t_render *r = params->render;
    const t_textures *texs = params->textures;
    
    bool catched = p->catch && draw.side == 6;  // Use side instead of r->side
    
    t_texture *wall_side = get_wall_side(draw.side, texs, p->level);  // Use side instead of r->side
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
        if(draw.dist > 450)
            break;
        if (catched)
        {
            if(p->level == 0)
                color = 225;
            if(p->level == 1)
                color = 0x00FF00;
            if(p->level == 2)
                color = 0xFF0000;
        }
        else
        {
            color = get_pixel_from_image(wall_side, draw.tex_x, tex_y);
            color = darken_color(color, (float)draw.dist / 450);
        }
        put_pixel(draw.start_x, start_y, color, r);
        tex_y += step;
        start_y++;
    }
}
