/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:57:03 by escura            #+#    #+#             */
/*   Updated: 2024/07/19 12:10:47 by btvildia         ###   ########.fr       */
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

static void	draw_player(void)
{
	const t_cube	*c = cube();
	const t_player	*p = player();

	draw_cube(p->x_px, p->y_px, 5, 0x00FF0000);
}

void render_player(void) 
{
	t_cube *c = cube();
	t_player *p = player();

	move_player();
	// draw_player();
}