/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/08/06 14:37:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int side = 6;

int calculate_direction(float x, float y, float angle)
{
	int sx = cos(angle) > 0 ? 1 : -1;
	int sy = sin(angle) > 0 ? 1 : -1;
	t_cube *c = cube();

	if (is_touching(x - sx, y))
	{
		c->tex_x = (int)x % BLOCK_SIZE;
		if (sy == 1)
			return 1;
		else
			return 3;
	}
	else if (is_touching(x, y - sy))
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
	float z_dir = p->z_dir;
	return (z_dir)*HEIGHT;
}

void draw_h_line(float height, int start_x)
{
	const t_cube *c = cube();
	int color = 0;
	float tex_y = 0;
	int end;
	int start_y = 0;

	float step = T_SIZE / height;

	// TODO: - doesn't work properly
	// if (height > HEIGHT)
	// {
	// 	tex_y = ((height - HEIGHT) * step / 2);
	// 	height = HEIGHT;
	// }

	if (side != 6)
		start_y = (player()->z * height + vert_offset());
	if (side == 6)
		start_y = ((player()->z - c->map->blocks[0].z) * height + vert_offset());
	end = start_y + height;

	while (start_y < end)
	{
		if (player()->catch && side == 6)
			color = 255;
		else
			color = get_pixel_from_image(c->tex_x, tex_y, side);
		put_pixel(start_x, start_y, color);
		tex_y += step;
		start_y++;
	}
}

void bouble_sort_dist(float dist[])
{
	int i = 0;
	int j = 0;
	float temp = 0;

	while (dist[i] != 0)
	{
		j = 0;
		while (dist[j] != 0)
		{
			if (dist[i] > dist[j])
			{
				temp = dist[i];
				dist[i] = dist[j];
				dist[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void draw_pixel(float x, float y, float angle, int start_x, float dist)
{
	float line_height = 0;
	side = calculate_direction(x, y, angle);
	line_height = (BLOCK_SIZE * HEIGHT) / dist;
	draw_h_line(line_height, start_x);
}

bool handle_pixel_drawing(float x, float y)
{
	static bool save = false;
	
	t_cube *c = cube();

	if (is_touching(x, y))
	{
		if (!save)
		{
			save = true;
			return true;
		}
		
	}
	else if (save)
	{
		save = false;
		return true;
	}
	return false;
}

t_ray draw_line(float angle, int start_x)
{
	t_player *p = player();
	t_ray ray;
	float x = p->x_px;
	float y = p->y_px;
	float cosangle = cos(angle);
	float sinangle = sin(angle);
	ray.angle = angle;
	ray.start_x = start_x;
	ray.dist = 0;
	ray.distances = ft_malloc(sizeof(float) * 100);
	ray.x = ft_malloc(sizeof(float) * 100);
	ray.y = ft_malloc(sizeof(float) * 100);
	int i = 0;

	while (!touch_edge(x, y))
	{
		if(handle_pixel_drawing(x, y))
		{
			ray.x[i] = x;
			ray.y[i] = y;
			ray.dist = view_lane_distance(x, y, angle);
			ray.distances[i] = ray.dist;
			draw_pixel(ray.x[i], ray.y[i], angle, start_x, ray.distances[i]);
			i++;
		}
		x += cosangle;
		y += sinangle;
	}
	
	while(i > 0)
	{
		i--;
		if (ray.distances[i] != 0)
			draw_pixel(ray.x[i], ray.y[i], angle, start_x, ray.distances[i]);
	}

	
	ft_free(ray.distances);
	ft_free(ray.x);
	ft_free(ray.y);
	return ray;
}

void render_view()
{
	t_cube *c = cube();

	float angle = player()->angle;
	int i = 0;
	
	t_ray ray[WIDTH];
	float fovInRadians = player()->fov * PI / 180;
	float halfFovInRadians = fovInRadians / 2.0;
	float angleOffset = angle - halfFovInRadians;

	while (i < WIDTH)
	{
		float fraction = (float)i / WIDTH;
		float rayAngle = angleOffset + fraction * fovInRadians;
		ray[i] = draw_line(rayAngle, i);
		i++;
	}

	// i = 0;
	// while (ray[i].start_x < WIDTH)
	// {
	// 	// draw_pixel(ray[i].x, ray[i].y, angle, ray[i].start_x, ray[i].distances);
	// 	i++;
	// }
}