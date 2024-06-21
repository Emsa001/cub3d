/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/06/21 17:37:47 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(void)
{
	const t_cube	*c = cube();
	int				i;
	int				j;
	int				color;

	i = 0;
	color = (c->map->c[0] << 16) + (c->map->c[1] << 8) + c->map->c[2];
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_pixel_put(c->mlx, c->win, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_floor(void)
{
	const t_cube	*c = cube();
	int				i;
	int				j;
	int				color;

	i = HEIGHT / 2;
	color = (c->map->f[0] << 16) + (c->map->f[1] << 8) + c->map->f[2];
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_pixel_put(c->mlx, c->win, j, i, color);
			j++;
		}
		i++;
	}
}

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

int	get_currect_pixel_color(int j, int line_height, int i)
{
	const t_cube	*c = cube();
	int				color;
	int				x;
	int				y;
	int				pos;

	x = j / line_height + i;
	y = j * 64 / line_height;
	pos = y * 64 + x;
	color = c->texture->addr[pos];
	return (color);
}

void	draw_texture_line(int line_height, int i)
{
	const t_cube	*c = cube();
	const t_player	*p = player();
	int				j;
	int				color;

	j = 0;
	color = 0x00FF0000;
	while (j < line_height)
	{
		color = get_currect_pixel_color(j, line_height, i);
		mlx_pixel_put(c->mlx, c->win, c->x, c->y + j - line_height / 2, color);
		j++;
	}
}

void	draw_wall(float x, float y, float angle, int side, int i)
{
	const t_cube	*c = cube();
	const t_player	*p = player();
	float			dist;
	int				line_height;
	int				blue_intensity;

	dist = view_lane_distance(x, y, angle);
	line_height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	draw_texture_line(line_height, i);
}

void	draw_line(float angle, int i)
{
	float x = player()->x_px;
	float y = player()->y_px;

	int sx = player()->x_dir > 0 ? 1 : -1;
	int sy = player()->y_dir > 0 ? 1 : -1;

	static int side;

	while (!is_touching(x, y, WALL))
	{
		mlx_pixel_put(cube()->mlx, cube()->win, x, y, side);
		x += cos(angle);
		y += sin(angle);
	}

	if (is_touching((x - sx), y, WALL))
		side = 255;
	else if (is_touching(x, (y - sy), WALL))
		side = 125;

	draw_wall(x, y, angle, side, i);
}