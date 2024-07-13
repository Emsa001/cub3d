/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/07/13 18:06:18 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int col = 0;

void draw_h_line(float height, float tex_x)
{
    const t_cube *c = cube();
    int color = col;
    int start = (HEIGHT - height) / 2;
    int end = start + height;

	float step = 450 / height;
	float y = 0;
	
    while (start < end)
    {
        color = get_pixel_from_image(tex_x, y);
        put_pixel(c->x, start, color);
		y += step;
        start++;
    }
}

void draw_wall(float x, float y, float angle, float tex_x)
{
	float dist;
	float line_height;

	dist = view_lane_distance(x, y, angle);
	line_height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	draw_h_line(line_height, tex_x);
}

void	draw_line(float angle)
{
	t_player *p = player();
	float x = p->x_px;
	float y = p->y_px;
	
	int sx = cos(angle) > 0 ? 1 : -1;
	int sy = sin(angle) > 0 ? 1 : -1;

	static int color = 255;
	float tex_x = 0;

	while(!is_touching(x, y, WALL))
	{
		put_pixel(x, y, color);
		x += cos(angle);
		y += sin(angle);
	}
	
	tex_x = (int)y % BLOCK_SIZE;
	if (is_touching((x - sx), y, WALL))
	{
		tex_x = (int)x % BLOCK_SIZE;
		color = 255;
	}
	else if (is_touching(x, (y - sy), WALL))
	{
		tex_x = (int)y % BLOCK_SIZE;
		color = 125;
	}
	col = color;
	
	tex_x = tex_x / BLOCK_SIZE * 450;
	
	draw_wall(x, y, angle, tex_x);
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
