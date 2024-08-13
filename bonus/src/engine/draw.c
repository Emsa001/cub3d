/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/08/13 22:47:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int calculate_direction(float x, float y, float angle, t_cube *c)
{
    int sx = cos(angle) > 0 ? 1 : -1; 
    int sy = sin(angle) > 0 ? 1 : -1;

    if (is_touching(x - sx, y) || is_touching(x - sx, y - sy)) {
        c->tex_x = (int)x % BLOCK_SIZE;
        return (sy == 1) ? 1 : 3;
    } else if (is_touching(x, y - sy)|| is_touching(x, y)) {
        c->tex_x = (int)y % BLOCK_SIZE;
        return (sx == 1) ? 2 : 4;
    } else if (touch_block(c->map->doors, x - sx, y)) {
        c->tex_x = (int)x % BLOCK_SIZE;
        return 5;
    } else if (touch_block(c->map->doors, x, y - sy)) {
        c->tex_x = (int)y % BLOCK_SIZE;
        return 5;
    } else if (touch_block(c->map->blocks, x - sx, y)) {
        c->tex_x = (int)x % BLOCK_SIZE;
        return 6;
    } else if (touch_block(c->map->blocks, x, y - sy)) {
        c->tex_x = (int)y % BLOCK_SIZE;
        return 6;
    }
    return 0;
}

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

    r = r - (r * ratio);
    g = g - (g * ratio);
    b = b - (b * ratio);

    if (r < 0)
        r = 0;

    if (g < 0)
        g = 0;

    if (b < 0)
        b = 0;

    return (r << 16) | (g << 8) | b;
}

void draw_floor(int height, int start_x, ThreadParams *params, float angle)
{
    const t_cube *c = params->cube;
    const t_player *p = params->player;
    const t_textures *texs = params->textures;
    int start_y = HEIGHT / 2 + height / 2;
    float floor_x = 0;
    float floor_y = 0;
    
    float cosangle = cos(angle);
    float sinangle = sin(angle);
    int color = 0;

    float current_dist = 0;

    t_texture *floor = texs->floor;

    while (start_y < HEIGHT)
    {
        current_dist = (HEIGHT / (2.0 * start_y - HEIGHT)) * (p->z + 1.5);
        
        floor_x = (p->x) + current_dist * cosangle;
        floor_y = (p->y) + current_dist * sinangle;

        color = get_pixel_from_image(floor, floor_x * T_SIZE, floor_y * T_SIZE);

        color = darken_color(color, (float)current_dist / 7);

        put_pixel(start_x, start_y, color);

        start_y++;
    }
}

static void draw_wall(int height, int start_x, ThreadParams *params, int dist)
{
    const t_cube *c = params->cube;
    const t_player *p = params->player;
    const t_render *r = params->render;
    const t_textures *texs = params->textures;
    t_texture *wall_side = get_wall_side(r->side, texs);
    if(!wall_side)
        return;
    
    int color = 0;
    float tex_y = 0;
    int start_y = 0;
    int end = 0;
    float step;
    step = T_SIZE / (float) height;
    start_y = (p->z * height + vert_offset(p));
    
    if(height > HEIGHT)
        end = HEIGHT;
    else
        end = start_y + height;
            
    while (start_y < end) 
    {
        if (p->catch && r->side == 6)
            color = 255;
        else
            color = get_pixel_from_image(wall_side, c->tex_x, tex_y);
        
        color = darken_color(color, (float)dist / 500);

        put_pixel(start_x, start_y, color);
        tex_y += step;
        start_y++;
    }   
}

// ray-casting algorithm

static bool find_hitbox(float x, float y, t_cube *c)
{
    if (is_touching(x, y))
        return false;
    if (touch_block(c->map->blocks, x, y))
        return false;
    if (touch_block(c->map->doors, x, y))
        return false;
    return true;
}

void draw_line(float angle, int start_x, ThreadParams *params)
{
    t_cube *c = params->cube;
    t_render *r = params->render;
    const t_player *p = params->player;
    float cosangle = cos(angle);
    float sinangle = sin(angle);

    float x = p->x_px;
    float y = p->y_px;

    bool save = false;
    int i = 0;
    int dist;
    while(find_hitbox(x, y, c))
    {
        dist = view_lane_distance(x, y, angle);
        if(dist > 500)
            break;
        x = x + cosangle;
        y = y + sinangle;
    }
    
    pthread_mutex_lock(params->mutex);
    
    r->side = calculate_direction(x, y, angle, c);
    int line_height = (BLOCK_SIZE * HEIGHT) / dist;

    draw_floor(line_height, start_x, params, angle);
    draw_wall(line_height, start_x, params, dist);
    
    pthread_mutex_unlock(params->mutex);

}

// // Ray-casting + Painter's algorithm algorithm

// void draw_pixel(t_ray ray, float angle, int start_x, ThreadParams *params) 
// {
//     t_render *r = params->render;
//     r->side = calculate_direction(ray.x, ray.y, angle, params->cube);
//     int line_height = (BLOCK_SIZE * HEIGHT) / ray.dist;
//     // draw_wall(line_height, start_x, params, ray.dist);
//     draw_floor(line_height, start_x, params, angle);
// }

// bool touch_side(float x, float y, t_state *state)
// {
//     t_cube *c = cube();
//     if (is_touching(x, y))
//     {
//         if (!state->save)
//         {
//             state->save = true;
//             return true;
//         }
//     }
//     else if (touch_block(c->map->blocks, x, y))
//     {
//         if (!state->block)
//         {
//             state->block = true;
//             return true;
//         }
//     }
//     else if (touch_block(c->map->doors, x, y))
//     {
//         if (!state->door)
//         {
//             state->door = true;
//             return true;
//         }
//     }
//     else if (state->save || state->block || state->door)
//     {
//         state->save = false;
//         state->block = false;
//         state->door = false;
//         return true;
//     }
//     return false;
// }

// void draw_line(float angle, int start_x, ThreadParams *params)
// {
//     t_cube *c = params->cube;
//     t_render *r = params->render;
//     const t_player *p = params->player;
//     float cosangle = cos(angle);
//     float sinangle = sin(angle);
//     int dist;

//     float x = p->x_px;
//     float y = p->y_px;
    
//     t_ray rays[MAX_SIZE];
//     t_state state = {false, false, false};
//     int i = 0;

//     r->ray_angle = angle;
//     while(!touch_edge(x, y))
//     {
//         dist = view_lane_distance(x, y, angle);
//         // if(dist > 450)
//         //     break;
//         if(touch_side(x, y, &state))
//         {
//             rays[i].dist = dist;
//             rays[i].x = x;
//             rays[i].y = y;
//             i++;
//         }
//         x += cosangle;
//         y += sinangle;
//     }
    
//     pthread_mutex_lock(params->mutex);
    
//     while (i > 0)
//     {
//         i--;
//         if(rays[i].dist != 0)
//             draw_pixel(rays[i], angle, start_x, params);
//     }
    
//     pthread_mutex_unlock(params->mutex);
// }
