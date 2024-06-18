/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/06/18 15:42:19 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	p_x = 200;
float	p_y = 200;
float	p_a = PI / 2;

float	p_d_x = 0;
float	p_d_y = 0;

int		pr_w = 0;
int		pr_s = 0;
int		pr_a = 0;
int		pr_d = 0;

void	draw_line(t_cube *p, float x1, float y1, float x2, float y2, int color)
{
	float	dx;
	float	dy;
	float	len;
	float	x;
	float	y;
	int		i;

	dx = x2 - x1;
	dy = y2 - y1;
	len = sqrt(dx * dx + dy * dy);
	dx /= len;
	dy /= len;
	x = x1;
	y = y1;
	i = 0;
	while (i < len)
	{
		mlx_pixel_put(p->mlx, p->win, x, y, color);
		x += dx;
		y += dy;
		i++;
	}
}

void	draw_arrow(t_cube *p)
{
	float	x;
	float	y;

	x = p_x + p_d_x * 10;
	y = p_y + p_d_y * 10;
	draw_line(p, p_x, p_y, x, y, 0x00FFFF00);
}

void	draw_player(t_cube *p)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		mlx_pixel_put(p->mlx, p->win, p_x + i - 2.5, p_y - 2.5, 0x00FF0000);
		mlx_pixel_put(p->mlx, p->win, p_x - 2.5, p_y + i - 2.5, 0x00FF0000);
		mlx_pixel_put(p->mlx, p->win, p_x + i - 2.5, p_y + 2.5, 0x00FF0000);
		mlx_pixel_put(p->mlx, p->win, p_x + 2.5, p_y + i - 2.5, 0x00FF0000);
		i++;
	}
}

int	movement(void)
{
	if (pr_a)
	{
		p_a -= 0.1;
		if (p_a < 0)
			p_a += 2 * PI;
		p_d_x = cos(p_a) * 5;
		p_d_y = sin(p_a) * 5;
	}
	if (pr_d)
	{
		p_a += 0.1;
		if (p_a > 2 * PI)
			p_a -= 2 * PI;
		p_d_x = cos(p_a) * 5;
		p_d_y = sin(p_a) * 5;
	}
	if (pr_w)
	{
		p_x += p_d_x;
		p_y += p_d_y;
	}
	if (pr_s)
	{
		p_x -= p_d_x;
		p_y -= p_d_y;
	}
	return (0);
}
int	kd(int kc)
{
	if (kc == ESC)
		exit(0);
	if (kc == W)
		pr_w = 1;
	if (kc == S)
		pr_s = 1;
	if (kc == A)
		pr_a = 1;
	if (kc == D)
		pr_d = 1;
	return (0);
}
 
int	ku(int kc)
{
	if (kc == W)
		pr_w = 0;
	if (kc == S)
		pr_s = 0;
	if (kc == A)
		pr_a = 0;
	if (kc == D)
		pr_d = 0;
	return (0);
}

int	draw(t_cube *p)
{
	void	*wall;
	int		i;
	int		j;

	usleep(16666);
	mlx_clear_window(p->mlx, p->win);
	wall = mlx_xpm_file_to_image(p->mlx, "src/textures/Square.xpm", &(int){0},
			&(int){0});
	i = 0;
	j = 0;
	while (i < p->map->height)
	{
		j = 0;
		while (j < p->map->width)
		{
			if (p->map->map[i][j] == '1')
				mlx_put_image_to_window(p->mlx, p->win, wall, j * 64, i * 64);
			j++;
		}
		i++;
	}
	draw_player(p);
	draw_arrow(p);
	movement();
	return (0);
}

void	play(void)
{
	t_cube	*c;

	c = cube();
	print_map_info();
	p_x = player()->x * 64;
	p_y = player()->y * 64;
	p_a = player()->a;
	c->win = mlx_new_window(c->mlx, c->map->width * 64, c->map->height * 64,
			"Cub3D");
	mlx_do_key_autorepeatoff(c->mlx);
	mlx_hook(c->win, KeyPress, KeyPressMask, kd, (void *)c);
	mlx_hook(c->win, KeyRelease, KeyReleaseMask, ku, (void *)c);
	mlx_loop_hook(c->mlx, draw, (void *)c);
	mlx_loop(c->mlx);
}
