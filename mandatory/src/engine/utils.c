/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:30:33 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 12:22:27 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool is_touching(float px, float py)
{
	const int		x = px / BLOCK_SIZE;
	const int		y = py / BLOCK_SIZE;
	const t_cube	*c = cube();

	if (x < 0 || y < 0 || x >= c->map->width || y >= c->map->height)
		return (true);
	if (c->map->map[y][x] == WALL)
		return (true);
    return (false);
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

