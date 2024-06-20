/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/06/20 15:36:47 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	c = cube();
	// print_map_info();
	c->win = mlx_new_window(c->mlx, WIDTH, HEIGHT, "Cub3D");
	init_hooks();
}
