/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/09/30 11:28:31 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	calculate_direction(float x, float y, float angle, int dir)
{
	int	sx;
	int	sy;

	sx = -1;
	sy = -1;
	if (cos(angle) > 0)
		sx = 1;
	if (sin(angle) > 0)
		sy = 1;
	if (is_touching(x - sx, y) || is_touching(x - sx, y - sy))
	{
		cube()->tex_x = (int)x % BLOCK_SIZE;
		dir = 1;
		if (sy == 1)
			dir = 2;
	}
	else if (is_touching(x, y - sy) || is_touching(x, y))
	{
		cube()->tex_x = (int)y % BLOCK_SIZE;
		dir = 3;
		if (sx == 1)
			dir = 4;
	}
	return (dir);
}

void	draw_h_line(float height, int start_x)
{
	int		color;
	float	tex_y;
	int		end;
	int		start_y;
	float	step;

	color = 0;
	tex_y = 0;
	step = T_SIZE / height;
	if (height > HEIGHT)
	{
		tex_y = (height - HEIGHT) * step / 2;
		height = HEIGHT;
	}
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		color = get_pixel_from_image(cube()->tex_x, tex_y, render()->side);
		put_pixel(start_x, start_y, color);
		tex_y += step;
		start_y++;
	}
}

void	draw_line(float angle, int start_x)
{
	float	x;
	float	y;
	float	dist;
	float	line_height;

	x = player()->x_px;
	y = player()->y_px;
	while (!is_touching(x, y))
	{
		x += cos(angle);
		y += sin(angle);
	}
	render()->side = calculate_direction(x, y, angle, 0);
	dist = view_lane_distance(x, y, angle);
	line_height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	draw_h_line(line_height, start_x);
}

void	render_view(void)
{
	t_cube	*c;
	int		i;
	float	fov_in_radians;
	float	angle_offset;
	float	ray_angle;

	c = cube();
	i = 0;
	fov_in_radians = player()->fov * PI / 180;
	angle_offset = player()->angle - fov_in_radians / 2.0;
	while (i < WIDTH)
	{
		ray_angle = angle_offset + ((float)i / WIDTH) * fov_in_radians;
		draw_line(ray_angle, i);
		i++;
	}
}
