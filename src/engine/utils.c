/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:30:33 by escura            #+#    #+#             */
/*   Updated: 2024/06/20 17:11:08 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_touching(float px, float py, char c)
{
	int	x;
	int	y;

	x = px / BLOCK_SIZE;
	y = py / BLOCK_SIZE;
	return (cube()->map->map[y][x] && cube()->map->map[y][x] == c);
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
