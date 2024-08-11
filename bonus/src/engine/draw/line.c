/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:46:18 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 16:09:13 by escura           ###   ########.fr       */
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

static void draw_pixel(t_ray ray, float angle, int start_x, ThreadParams *params) 
{
    t_cube *c = params->cube;
    t_render *r = params->render;
    
    r->side = calculate_direction(ray.x, ray.y, angle, c);
    float line_height = (BLOCK_SIZE * HEIGHT) / ray.dist;
    draw_wall(line_height, start_x);
}

static bool handle_pixel_drawing(float x, float y, t_cube *c)
{
	static bool save = false;
	static bool block = false;
	static bool door = false;
	
	if (is_touching(x, y, c))
	{
		if (!save)
		{
			save = true;
			return true;
		}
	}
	else if(touch_block(c->map->blocks, x, y))
	{
		if (!block)
		{
			block = true;
			return true;
		}
	}
	else if(touch_block(c->map->doors, x, y))
	{
		if (!door)
		{
			door = true;
			return true;
		}
	}
	else if(save || block || door)
	{
		save = false;
		block = false;
		door = false;
		return true;
	}
	return false;
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
    t_ray rays[MAX_SIZE];
    int i = 0;

    while (!touch_edge(x, y, c)) {
        if (handle_pixel_drawing(x, y, c)) {
            rays[i].dist = view_lane_distance(x, y, angle);
            rays[i].x = x;
            rays[i].y = y;
            i++;
        }
        x += cosangle;
        y += sinangle;
    }

    pthread_mutex_lock(params->mutex);

    while (i > 0) {
        i--;
        if (rays[i].dist != 0) {
            draw_pixel(rays[i], angle, start_x, params);
        }
    }
    pthread_mutex_unlock(params->mutex);

}
