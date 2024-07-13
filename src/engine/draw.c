/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/07/13 21:45:25 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int side = 1;

void draw_h_line(float height, float tex_x)
{
    const t_cube *c = cube();
	t_player *p = player();
    int color = 0;
	float y = 0;
    int end;
	int start;
	float step = 450 / height;
	
	float vertical_offset = (p->z_dir * 0.5) * HEIGHT;
	
	if(height > HEIGHT)
	{
		y = (height - HEIGHT) * step / 2;
		height = HEIGHT;
	}
    start = (HEIGHT - height) / 2 + vertical_offset;
	end = start + height;
    while (start < end)
    {
		color = get_pixel_from_image(tex_x, y, side);
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
	draw_h_line(line_height, tex_x);
}

void	draw_line(float angle)
{
	t_player *p = player();
	float x = p->x_px;
	float y = p->y_px;
	
	int sx = cos(angle) > 0 ? 1 : -1;
	int sy = sin(angle) > 0 ? 1 : -1;
	float tex_x = 0;
	
	while(!is_touching(x, y, WALL))
	{
		x += cos(angle);
		y += sin(angle);
	}
	
	tex_x = (int)y % BLOCK_SIZE;
	if (is_touching(x - sx, y, WALL))
	{
		tex_x = (int)x % BLOCK_SIZE;
		side = 1;
	}
	else if (is_touching(x, y - sy, WALL))
	{
		tex_x = (int)y % BLOCK_SIZE;
		side = 2;
	}
	
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