/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:52:35 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 20:30:14 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_error(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit_game(1);
}

void	exit_game(int code)
{
	t_textures	*t;
	t_cube		*c;

	c = cube();
	if (!code)
	{
		t = textures();
		if (t)
		{
			mlx_destroy_image(c->mlx, t->wall_north->image);
			mlx_destroy_image(c->mlx, t->wall_south->image);
			mlx_destroy_image(c->mlx, t->wall_east->image);
			mlx_destroy_image(c->mlx, t->wall_west->image);
			mlx_destroy_window(c->mlx, c->win);
		}
	}
	mlx_destroy_display(c->mlx);
	free(c->mlx);
	ft_destructor();
	exit(code);
}
