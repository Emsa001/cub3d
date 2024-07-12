/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/07/12 20:26:08 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int col = 0;

void	draw_h_line(float height, float distance)
{
	const t_cube *c = cube();
	int i = 0;
	
	float texture_y = 0;
	float step = 450 / height;
	int color = col;
	int y = 0;
	while (i < height / 2)
	{
		y = (int)texture_y % 450;
		color = get_pixel_from_image(c->x, y);
		put_pixel(c->x, HEIGHT / 2 - i, color);
		put_pixel(c->x, HEIGHT / 2 + i, color);
		texture_y += step;
		i++;
	}
}

void draw_wall(float x, float y, float angle)
{
	const t_cube *c = cube();
	const t_player *p = player();
	float dist;
	float line_height;

	dist = view_lane_distance(x, y, angle);
	line_height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	if(line_height > HEIGHT)
		line_height = HEIGHT;
	draw_h_line(line_height, dist);
}

void	draw_line(float angle)
{
	float x = player()->x_px;
	float y = player()->y_px;
	
	int sx = player()->x_dir > 0 ? 1 : -1;
	int sy = player()->y_dir > 0 ? 1 : -1;

	static int color;
	int texture_x;

	while(!is_touching(x, y, WALL))
	{
		put_pixel(x, y, color);
		x += cos(angle);
		y += sin(angle);
	}
	
	if (is_touching((x - sx), y, WALL))
		color = 255;
	else if (is_touching(x, (y - sy), WALL))
		color = 125;
	col = color;
	draw_wall(x, y, angle);
}

void render_view()
{
	t_cube *c = cube();

	float angle = player()->angle;
	int numRays = WIDTH;
	int i = 0;

	float fovInRadians = player()->fov * PI / 180;
	float halfFovInRadians = fovInRadians / 2.0;
	float angleOffset = angle - halfFovInRadians;

	float rayWidth = (float)WIDTH / numRays; 

	while (i < numRays) 
    {
		float fraction = (float)i / numRays;
		float rayAngle = angleOffset + fraction * fovInRadians;
		draw_line(rayAngle);
		c->x = rayWidth * i;
		i++;
	}
}