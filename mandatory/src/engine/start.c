/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 20:31:07 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_floor(void)
{
	const t_cube	*c = cube();
	t_render		*r;
	int				x;
	int				y;

	r = render();
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, c->map->f);
			x++;
		}
		y++;
	}
}

void	draw_ceeling(void)
{
	const t_cube	*c = cube();
	t_render		*r;
	int				x;
	int				y;

	r = render();
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, c->map->c);
			x++;
		}
		y++;
	}
}

int	render_scene(void)
{
	t_render	*r;

	r = render();
	r->img_ptr = mlx_new_image(r->mlx, WIDTH, HEIGHT);
	draw_floor();
	draw_ceeling();
	render_view();
	mlx_put_image_to_window(r->mlx, r->win, r->img_ptr, 0, 0);
	mlx_destroy_image(r->mlx, r->img_ptr);
	move_player();
	return (0);
}

void	start_game(void)
{
	t_cube	*c;

	c = cube();
	c->win = mlx_new_window(c->mlx, WIDTH, HEIGHT, "Cub3D");
	render()->win = c->win;
	init_hooks();
}
