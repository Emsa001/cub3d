/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:30:33 by escura            #+#    #+#             */
/*   Updated: 2024/07/16 17:59:02 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool is_touching(float px, float py, char c)
{
	int		x = px / BLOCK_SIZE;
	int		y = py / BLOCK_SIZE;

	if(cube()->map->map[y][x] && cube()->map->map[y][x] == c)
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

void draw_cross_in_centre(void)
{
    const t_cube *c = cube();
    int x_center = WIDTH / 2;
    int y_center = HEIGHT / 2;
    int i = -7;

    while (i <= 7)
	{
		mlx_pixel_put(c->mlx, c->win, x_center + i, y_center, 0x0000FF00);
		mlx_pixel_put(c->mlx, c->win, x_center, y_center + i, 0x0000FF00);
		i++;
	}
}
