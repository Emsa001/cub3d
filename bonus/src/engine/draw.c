/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 15:40:05 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int calculate_direction(float x, float y, float angle, t_cube *c)
{
	int sx = cos(angle) > 0 ? 1 : -1;
	int sy = sin(angle) > 0 ? 1 : -1;
	t_cube *c = cube();

	if (is_touching(x - sx, y) || is_touching(x - sx, y - sy))
	{
		c->tex_x = (int)x % BLOCK_SIZE;
		if (sy == 1)
			return 1;
		else
			return 3;
	}
	else if (is_touching(x, y - sy) || is_touching(x, y))
	{
		c->tex_x = (int)y % BLOCK_SIZE;
		if (sx == 1)
			return 2;
		else
			return 4;
	}
	else if (touch_block(c->map->doors, x - sx, y))
	{
		c->tex_x = (int)x % BLOCK_SIZE;
		return 5;
	}
	else if (touch_block(c->map->doors, x, y - sy))
	{
		c->tex_x = (int)y % BLOCK_SIZE;
		return 5;
	}
	else if (touch_block(c->map->blocks, x - sx, y))
	{
		c->tex_x = (int)x % BLOCK_SIZE;
		return 6;
	}
	else if (touch_block(c->map->blocks, x, y - sy))
	{
		c->tex_x = (int)y % BLOCK_SIZE;
		return 6;
	}
	return 6;
}

int vert_offset() 
{
    t_player *p = player();
    return (p->z_dir) * HEIGHT;
}


void draw_wall(float height, int start_x) {
    const t_cube *c = cube();
    int color = 0;
    float tex_y = 0;
    int end;
    int start_y = 0;

    float step = T_SIZE / height;

    if (height > HEIGHT) {
        tex_y = ((height - HEIGHT) * step / 2);
        height = HEIGHT;
    }

    t_player *p = player();
    if (side != 6) {
        start_y = (p->z * height + vert_offset());
    } else {
        start_y = ((p->z - c->map->blocks[0].z) * height + vert_offset());
    }
    end = start_y + height;

    while (start_y < end) {
        if (p->catch && side == 6) {
            color = 255;
        } else {
            color = get_pixel_from_image(c->tex_x, tex_y, side);
        }
        put_pixel(start_x, start_y, color);
        tex_y += step;
        start_y++;
    }
}


void draw_pixel(t_ray ray, float angle, int start_x) 
{
    side = calculate_direction(ray.x, ray.y, angle);
    float line_height = (BLOCK_SIZE * HEIGHT) / ray.dist;
    draw_wall(line_height, start_x);
}


bool handle_pixel_drawing(float x, float y)
{
	static bool save = false;
	static bool block = false;
	static bool door = false;
	
	t_cube *c = cube();

	if (is_touching(x, y))
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

void draw_line(float angle, int start_x) {
    t_player *p = player();
    float cosangle = cos(angle);
    float sinangle = sin(angle);
    float x = p->x_px;
    float y = p->y_px;
    t_ray rays[MAX_SIZE];
    int i = 0;

    while (!touch_edge(x, y)) {
        if (handle_pixel_drawing(x, y)) {
            rays[i].dist = view_lane_distance(x, y, angle);
            rays[i].x = x;
            rays[i].y = y;
            i++;
        }
        x += cosangle;
        y += sinangle;
    }

    while (i > 0) {
        i--;
        if (rays[i].dist != 0) {
            draw_pixel(rays[i], angle, start_x);
        }
    }
}

void render_view()
{
	t_cube *c = cube();

	float angle = player()->angle;
	int i = 0;
	
	float fovInRadians = player()->fov * PI / 180;
	float halfFovInRadians = fovInRadians / 2.0;
	float angleOffset = angle - halfFovInRadians;

	while (i < WIDTH)
	{
		float fraction = (float)i / WIDTH;
		float rayAngle = angleOffset + fraction * fovInRadians;
		draw_line(rayAngle, i);
		i++;
	}
}

