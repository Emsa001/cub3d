/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/07/19 19:08:15 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int side = 1;

int calculate_direction(float x, float y, float angle)
{
	int sx = cos(angle) > 0 ? 1 : -1; 
	int sy = sin(angle) > 0 ? 1 : -1;

	if(is_touching(x - sx, y))
	{
		cube()->tex_x = (int)x % BLOCK_SIZE;
		if (sy == 1)
			return 1;
		else
			return 3;
	}
	else if(is_touching(x, y - sy))
	{
		cube()->tex_x = (int)y % BLOCK_SIZE;
		if (sx == 1)
			return 2;
		else
			return 4;
	}
	return 0;
}

void draw_h_line(float height, int start_x)
{
    const t_cube *c = cube();
    int color = 0;
	float tex_y = 0;
    int end;
	int start_y;
	
	float step = T_SIZE / height;
	
	if(height > HEIGHT)
	{
		tex_y = (height - HEIGHT) * step / 2;
		height = HEIGHT;
	}
    start_y = (HEIGHT - height) / 2;
	
	end = start_y + height;
    while (start_y < end)
    {
		color = get_pixel_from_image(c->tex_x, tex_y, side);
        put_pixel(start_x , start_y, color);
		tex_y += step;
        start_y++;
    }
}

void	draw_line(float angle , int start_x)
{
	t_player *p = player();
	float x = p->x_px;
	float y = p->y_px;
	float dist = 0;
	float line_height = 0;
	while(!is_touching(x, y))
	{
		x += cos(angle);
		y += sin(angle);
	}

	side = calculate_direction(x, y, angle);

	dist = view_lane_distance(x, y, angle);
	line_height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	draw_h_line(line_height, start_x);
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
