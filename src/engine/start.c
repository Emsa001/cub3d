/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 19:02:41 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_cube(int x, int y, int size, int col){
	int i = 0;
	const t_cube *c = cube();
	
	while (i < size)
	{
		mlx_pixel_put(c->mlx, c->win, x + i - size/2, y - 		size/2, col);
		mlx_pixel_put(c->mlx, c->win, x - 	size/2, y + i - 	size/2, col);
		mlx_pixel_put(c->mlx, c->win, x + i - size/2, y + 		size/2, col);
		mlx_pixel_put(c->mlx, c->win, x + 	size/2, y + i - 	size/2, col);
		i++;
	}
}

void draw_wall(int x, int y){

	const t_cube *c = cube();
	const float dist = view_lane_distance(x, y);
	const float height = 400;

	int i = 0;
	while(i < height){
		int color = 0x0060a5fa;
		if(dist > 50)
			color = 0x006366f1;
		if(dist > 100)
			color = 0x004f46e5;
		if(dist > 200)
			color = 0x004338ca;
	
		int size = WIDTH / cube()->map->width * BLOCK_SIZE;
		mlx_pixel_put(c->mlx, c->win, x, y + i, color);

		i++;
	}
}

void draw_line()
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
	int j = 0;
    while (i < WIDTH)
    {
		if(is_touching(x / BLOCK_SIZE, y / BLOCK_SIZE, WALL)){
			draw_cube(x, y, 3, 0x00FFF000);
			// draw_wall(x, y);
			j++;
			break;
		}

        mlx_pixel_put(c->mlx, c->win, x, y, 0x00FF0000);

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

	draw_cube(p->x_px, p->y_px, 5, 0x00FF0000);
}

int	render(t_cube *c)
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

	render_player();
	destroy_image(wall);
	
	return (0);
}

void	start_game(void)
{
	t_cube	*c;
	t_player *p;

	c = cube();
	// print_map_info();
	
	c->win = mlx_new_window(c->mlx, WIDTH, HEIGHT, "Cub3D");

	init_hooks();
}
