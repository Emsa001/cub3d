/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/06/20 11:54:33 by escura           ###   ########.fr       */
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

void	draw_h_line(float height, int color)
{
	const t_cube	*c = cube();
	int				i;

	i = 0;
	while (i < height / 2)
	{
		mlx_pixel_put(c->mlx, c->win, c->x, HEIGHT / 2 - i, color);
		mlx_pixel_put(c->mlx, c->win, c->x, HEIGHT / 2 + i, color);
		i++;
	}
}

float	get_ray_angle(int x, int y)
{
	const t_player	*p = player();
	float			angle;
	float			ca;

	ca = atan2f(y - p->y_px, x - p->x_px);
	angle = p->angle - ca;
	return (angle);
}

void	draw_wall(int x, int y)
{
	const t_cube	*c = cube();
	const t_player	*p = player();
	float			dist;
	float			line_height;
	int				blue_intensity;

	dist = distance(x, y);
	blue_intensity = 255 - (dist * 255 / 1000);
	if (blue_intensity < 0)
		blue_intensity = 0;
	line_height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	draw_h_line(line_height, blue_intensity);
}

void	draw_line(void)
{
	const int		len = 10000;
	const t_cube	*c = cube();
	t_player		*p;
	int				x;
	int				y;
	int				sx;
	int				sy;
	int				dx;
	int				dy;
	int				err;
	int				i;
	int				j;
	int				e2;

	p = player();
	x = p->x_px;
	y = p->y_px;
	p->x_dir = cos(p->angle) * 5;
	p->y_dir = sin(p->angle) * 5;
	sx = (p->x_dir > 0) ? 1 : -1;
	sy = (p->y_dir > 0) ? 1 : -1;
	dx = fabsf(p->x_dir * len);
	dy = fabsf(p->y_dir * len);
	err = dx - dy;
	i = 0;
	j = 0;
	while (i < WIDTH)
	{
		if (is_touching(x / BLOCK_SIZE, y / BLOCK_SIZE, WALL))
		{
			// draw_cube(x, y, 3, 0x00FFF000);
			draw_wall(x, y);
			j++;
			break ;
		}
		// mlx_pixel_put(c->mlx, c->win, x, y, 0x00FF0000);
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
		i++;
	}
}

void	draw_player(void)
{
	const t_cube	*c = cube();
	const t_player	*p = player();

	draw_cube(p->x_px, p->y_px, 5, 0x00FF0000);
}

void	draw_middle_line(void)
{
	const t_cube	*c = cube();
	int				i;

	i = 0;
	while (i < WIDTH)
	{
		mlx_pixel_put(c->mlx, c->win, i, HEIGHT / 2, 0x0000FF00);
		i++;
	}
}

int	render(t_cube *c)
{
	int		i;
	int		j;
	void	*wall;

	wall = load_image("assets/Square.xpm");
	usleep(16666);
	clean_window();
	i = 0;
	j = 0;
	while (i < c->map->height)
	{
		j = 0;
		while (j < c->map->width)
		{
			// if (c->map->map[i][j] == '1')
			// 	draw_image(wall, j * BLOCK_SIZE, i * BLOCK_SIZE);
			j++;
		}
		i++;
	}
	render_player();
	destroy_image(wall);
	draw_middle_line();
	return (0);
}

void	start_game(void)
{
	t_cube		*c;
	t_player	*p;

	c = cube();
	// print_map_info();
	c->win = mlx_new_window(c->mlx, WIDTH, HEIGHT, "Cub3D");
	init_hooks();
}
