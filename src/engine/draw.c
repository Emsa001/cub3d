/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/07/15 19:28:11 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int side = 1;

int calculate_direction(float x, float y, float angle)
{
	int sx = cos(angle) > 0 ? 1 : -1; 
	int sy = sin(angle) > 0 ? 1 : -1;

	if(is_touching(x - sx, y, WALL))
	{
		cube()->tex_x = (int)x % BLOCK_SIZE;
		if (sy == 1)
			return 1;
		else
			return 3;
	}
	else if(is_touching(x, y - sy, WALL))
	{
		cube()->tex_x = (int)y % BLOCK_SIZE;
		if (sx == 1)
			return 2;
		else
			return 4;
	}
	return 0;
}

int vert_offset(float z_dir)
{
	return (z_dir * 0.5) * HEIGHT;
}

void draw_h_line(float height)
{
    const t_cube *c = cube();
    int color = 0;
	float tex_y = 0;
    int end;
	int start;
	
	float step = T_SIZE / height;
	
	if(height > HEIGHT)
	{
		tex_y = (height - HEIGHT) * step / 2;
		height = HEIGHT;
	}
    start = (HEIGHT - height) / 2 + vert_offset(player()->z_dir);
	
	end = start + height;
    while (start < end)
    {
		color = get_pixel_from_image(c->tex_x, tex_y, side);
        put_pixel(c->x , start, color);
		tex_y += step;
        start++;
    }
}

void	draw_line(float angle)
{
	t_player *p = player();
	float x = p->x_px;
	float y = p->y_px;
	float dist = 0;
	float line_height = 0;
	
	while(!is_touching(x, y, WALL))
	{
		x += cos(angle);
		y += sin(angle);
	}

	dist = view_lane_distance(x, y, angle);
	line_height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	draw_h_line(line_height);
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
		draw_line(rayAngle);
		c->x = i;
		i++;
	}
}