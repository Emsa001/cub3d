/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/08/04 17:39:30 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int calculate_direction(float x, float y, float angle, t_cube *c)
{
    int sx = cos(angle) > 0 ? 1 : -1; 
    int sy = sin(angle) > 0 ? 1 : -1;

    if (is_touching(x - sx, y, c)) {
        c->tex_x = (int)x % BLOCK_SIZE;
        return (sy == 1) ? 1 : 3;
    } else if (is_touching(x, y - sy, c)) {
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
    return 6;
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
        t = texs->wall_west;
    return t;
}

static void draw_h_line(float height, int start_x, ThreadParams *params)
{
    
    const t_cube *c = params->cube;
    const t_player *p = params->player;
    const t_render *r = params->render;
    const t_textures *texs = params->textures;
    
    int color = 0;
    float tex_y = 0;
    int start_y = 0;
    int end = 0;
    float step = T_SIZE / height;

    if (height > HEIGHT) {
        tex_y = ((height - HEIGHT) * step / 2);
        height = HEIGHT;
    }

    start_y = (p->z * height + vert_offset(p));
    end = start_y + height;

    if(end > HEIGHT)
        end = HEIGHT;
        
    t_texture *wall_side = get_wall_side(r->side, texs);

    while (start_y < end) {
		// color = params->color;
        if (p->catch && r->side == 6)
            color = 255;
        else
            color = get_pixel_from_image(wall_side, c->tex_x, tex_y);
        put_pixel(start_x, start_y, color, params->render);
        tex_y += step;
        start_y++;
    }
}


static bool find_hitbox(float x, float y, t_cube *c)
{
    if (is_touching(x, y, c))
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

    float x = p->x_px;
    float y = p->y_px;

    while (find_hitbox(x, y, c)) {
        x += cos(angle);
        y += sin(angle);
    }
    const float dist = view_lane_distance(x, y, angle);
    const float line_height = (BLOCK_SIZE / dist) * (WIDTH / 2);
    
    pthread_mutex_lock(params->mutex);
    
    r->side = calculate_direction(x, y, angle, c);
    draw_h_line(line_height, start_x, params);

    pthread_mutex_unlock(params->mutex);

}
