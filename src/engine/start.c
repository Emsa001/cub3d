/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 13:59:51 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define COLOR 0x00FFFF00

void draw_lines()
{
	const int len = 10000;
    const t_cube *c = cube();
    t_player *p = player();

    int x = p->x_px;
    int y = p->y_px;

	p->x_dir = cos(p->angle) * 5;
	p->y_dir = sin(p->angle) * 5;

    int sx = (p->x_dir > 0) ? 1 : -1;
    int sy = (p->y_dir > 0) ? 1 : -1;
    int dx = fabsf(p->x_dir * len);
    int dy = fabsf(p->y_dir * len);
    int err = dx - dy;

    int i = 0;
    while (i < 1000)
    {
		if(is_touching(x / BLOCK_SIZE, y / BLOCK_SIZE, WALL))
			break;

        mlx_pixel_put(c->mlx, c->win, x, y, COLOR);

        int e2 = 2 * err;
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

void	draw_player()
{
	const t_cube *c = cube();
	const t_player *p = player();
	int	i;

	i = 0;
	while (i < 5)
	{
		mlx_pixel_put(c->mlx, c->win, p->x_px + i - 2.5, p->y_px - 		2.5, 0x00FF0000);
		mlx_pixel_put(c->mlx, c->win, p->x_px - 	2.5, p->y_px + i - 	2.5, 0x00FF0000);
		mlx_pixel_put(c->mlx, c->win, p->x_px + i - 2.5, p->y_px + 		2.5, 0x00FF0000);
		mlx_pixel_put(c->mlx, c->win, p->x_px + 	2.5, p->y_px + i - 	2.5, 0x00FF0000);
		i++;
	}
}

int	draw(t_cube *c)
{
	int		i;
	int		j;
	void *wall = load_image("assets/Square.xpm");

	usleep(16666);
	clean_window();

	i = 0;
	j = 0;
	while (i < c->map->height)
	{
		j = 0;
		while (j < c->map->width)
		{
			if (c->map->map[i][j] == '1')
				draw_image(wall, j * BLOCK_SIZE, i * BLOCK_SIZE);
			j++;
		}
		i++;
	}

	move_player();
	draw_player();

	float angle = player()->angle;

	player()->angle -= 0.01 * player()->fov;
	for(int i = 0; i < player()->fov * 2; i++){
		draw_lines();
		player()->angle += 0.01;
	}
	player()->angle = angle;
	
	destroy_image(wall);
	return (0);
}

void	start_game(void)
{
	t_cube	*c;
	t_player *p;

	c = cube();
	print_map_info();
	
	c->win = mlx_new_window(c->mlx, WIDTH, HEIGHT, "Cub3D");

	init_hooks();
}
