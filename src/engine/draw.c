/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/06/21 19:07:20 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cube(int x, int y, int size, int col)
{
	int				i;
	const t_cube	*c = cube();

	i = 0;
	while (i < size)
	{
		mlx_pixel_put(c->mlx, c->win, x + i - size / 2, y - size / 2, col);
		mlx_pixel_put(c->mlx, c->win, x - size / 2, y + i - size / 2, col);
		mlx_pixel_put(c->mlx, c->win, x + i - size / 2, y + size / 2, col);
		mlx_pixel_put(c->mlx, c->win, x + size / 2, y + i - size / 2, col);
		i++;
	}
}

void	draw_h_line(float height, float distance)
{
	const t_cube *c = cube();
	int i = 0;

	while (i < height / 2)
	{
		int color = get_pixel_from_image(c->x, HEIGHT / 2 - i);
		put_pixel(c->x, HEIGHT / 2 - i, color);

		color = get_pixel_from_image(c->x, HEIGHT / 2 + i);
		put_pixel(c->x, HEIGHT / 2 + i, color);
		i++;
	}
}

// void	draw_h_line(float height, int x)
// {
// 	const t_cube *c = cube();

// 	int y = 0;
//     while (y < height / 2) {
//         int color = get_pixel_from_image(x, HEIGHT / 2 + y);
//         put_pixel(x, y, color);
//         y++;
//     }
// }

void draw_wall(float x, float y, float angle, int color)
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

	while(!is_touching(x, y, WALL))
	{
		// put_pixel(x, y, color);
		x += cos(angle);
		y += sin(angle);
	}
	
	if (is_touching((x - sx), y, WALL))
		color = 255;
	else if (is_touching(x, (y - sy), WALL))
		color = 125;

	draw_wall(x, y, angle, color);
}