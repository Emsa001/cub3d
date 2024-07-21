/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:52:35 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 19:46:56 by btvildia         ###   ########.fr       */
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
	t_textures	*t = textures();

	mlx_destroy_image(cube()->mlx, t->wall_north->image);
	mlx_destroy_image(cube()->mlx, t->wall_south->image);
	mlx_destroy_image(cube()->mlx, t->wall_east->image);
	mlx_destroy_image(cube()->mlx, t->wall_west->image);

	ft_destructor();
	exit (1);
}
