/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/06/13 16:27:40 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		draw(t_cube *p);
float	p_x = 200;
float	p_y = 200;
float	p_a = PI / 2;

float	p_d_x = 0;
float	p_d_y = 0;

int		pr_w = 0;
int		pr_s = 0;
int		pr_a = 0;
int		pr_d = 0;

void	draw_touch(t_cube *p, float x, float y, int color)
{
	float	i;

	i = 0;
	while (i < 5)
	{
		mlx_pixel_put(p->mlx, p->win, x + i, y, color);
		mlx_pixel_put(p->mlx, p->win, x, y + i, color);
		mlx_pixel_put(p->mlx, p->win, x + i, y + 5, color);
		mlx_pixel_put(p->mlx, p->win, x + 5, y + i, color);
		i++;
	}
}

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
	len = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
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

float	dist(float ax, float ay, float bx, float by, float angle)
{
	(void)angle;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_rays(t_cube *p)
{
	float	nTan;
	float	dist_h;
	float	hx;
	float	hy;
	float	dist_v;
	float	vx;
	float	vy;

	float aTan, rx, ry, ra, xo, yo;
	int r, mx, my, mp, dof;
	ra = p_a - DR * 30;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	r = 0;
	while (r < 60)
	{
		dist_h = 100000;
		hx = p_x;
		hy = p_y;
		dof = 0;
		aTan = -1 / tan(ra);
		if (ra > PI)
		{
			ry = (((int)p_y >> 6) << 6) - 0.0001;
			rx = (p_y - ry) * aTan + p_x;
			yo = -64;
			xo = -yo * aTan;
		}
		else if (ra < PI)
		{
			ry = (((int)p_y >> 6) << 6) + 64;
			rx = (p_y - ry) * aTan + p_x;
			yo = 64;
			xo = -yo * aTan;
		}
		else
		{
			rx = p_x;
			ry = p_y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx >= 0 && mx < p->width && my >= 0 && my < p->height)
			{
				mp = my * p->width + mx;
				if (mp >= 0 && mp < p->width * p->height
					&& p->map[my][mx] == '1')
				{
					hx = rx;
					hy = ry;
					dist_h = dist(p_x, p_y, hx, hy, ra);
					dof = 8;
				}
				else
				{
					rx += xo;
					ry += yo;
					dof += 1;
				}
			}
			else
			{
				dof = 8;
			}
		}
		dof = 0;
		dist_v = 100000;
		vx = p_x;
		vy = p_y;
		nTan = -tan(ra);
		if (ra > P2 && ra < P3)
		{
			rx = (((int)p_x >> 6) << 6) - 0.0001;
			ry = (p_x - rx) * nTan + p_y;
			xo = -64;
			yo = -xo * nTan;
		}
		else if (ra < P2 || ra > P3)
		{
			rx = (((int)p_x >> 6) << 6) + 64;
			ry = (p_x - rx) * nTan + p_y;
			xo = 64;
			yo = -xo * nTan;
		}
		else
		{
			rx = p_x;
			ry = p_y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx >= 0 && mx < p->width && my >= 0 && my < p->height)
			{
				mp = my * p->width + mx;
				if (mp >= 0 && mp < p->width * p->height
					&& p->map[my][mx] == '1')
				{
					vx = rx;
					vy = ry;
					dist_v = dist(p_x, p_y, vx, vy, ra);
					dof = 8;
				}
				else
				{
					rx += xo;
					ry += yo;
					dof += 1;
				}
			}
			else
			{
				dof = 8;
			}
		}
		if (dist_v < dist_h)
		{
			rx = vx;
			ry = vy;
		}
		else
		{
			rx = hx;
			ry = hy;
		}
		draw_line(p, p_x, p_y, rx, ry, 0x00FFF000);
		draw_touch(p, rx, ry, 0x00FFF000);
		r++;
		ra += DR;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}

void	draw_player(t_cube *p)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		mlx_pixel_put(p->mlx, p->win, p_x + i, p_y, 0x00FFFF00);
		mlx_pixel_put(p->mlx, p->win, p_x, p_y + i, 0x00FFFF00);
		mlx_pixel_put(p->mlx, p->win, p_x + i, p_y + 5, 0x00FFFF00);
		mlx_pixel_put(p->mlx, p->win, p_x + 5, p_y + i, 0x00FFFF00);
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
		p_d_x = cos(p_a) * 2;
		p_d_y = sin(p_a) * 2;
	}
	if (pr_d)
	{
		p_a += 0.1;
		if (p_a > 2 * PI)
			p_a -= 2 * PI;
		p_d_x = cos(p_a) * 2;
		p_d_y = sin(p_a) * 2;
	}
	if (pr_w)
	{
		p_x += p_d_x * 3;
		p_y += p_d_y * 3;
	}
	if (pr_s)
	{
		p_x -= p_d_x * 3;
		p_y -= p_d_y * 3;
	}
	return (0);
}
int	kd(int kc)
{
    if(kc == ESC)
    {
        exit(0);
    }
	if (kc == W)
	{
		pr_w = 1;
	}
	if (kc == S)
	{
		pr_s = 1;
	}
	if (kc == A)
	{
		pr_a = 1;
	}
	if (kc == D)
	{
		pr_d = 1;
	}
	return (0);
}

int	ku(int kc)
{
	if (kc == W)
	{
		pr_w = 0;
	}
	if (kc == S)
	{
		pr_s = 0;
	}
	if (kc == A)
	{
		pr_a = 0;
	}
	if (kc == D)
	{
		pr_d = 0;
	}
	return (0);
}

int	draw(t_cube *p)
{
	void	*wall;

	usleep(16666);
	mlx_clear_window(p->mlx, p->win);
	wall = mlx_xpm_file_to_image(p->mlx, "src/textures/Square.xpm",
			&(int){0}, &(int){0});
	for (int y = 0; y < p->height; y++)
	{
		for (int x = 0; x < p->width; x++)
		{
			if (p->map[y][x] == '1')
			{
				mlx_put_image_to_window(p->mlx, p->win, wall, x * 64, y * 64);
			}
		}
	}
	draw_player(p);
	draw_rays(p);
	movement();
	return (0);
}

void	play(void)
{
    t_cube *c = cube();
    c->win = mlx_new_window(c->mlx, (c->width - 1) * 64, c->height * 64, "Cub3D");
    mlx_do_key_autorepeatoff(c->mlx);
    mlx_hook(c->win, KeyPress, KeyPressMask, kd, (void *)c);
    mlx_hook(c->win, KeyRelease, KeyReleaseMask, ku, (void *)c);
    mlx_loop_hook(c->mlx, draw, (void *)c);
    mlx_loop(c->mlx);
    free((void *)c);
}
