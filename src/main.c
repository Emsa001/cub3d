/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:20:57 by escura            #+#    #+#             */
/*   Updated: 2024/06/05 13:19:13 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void change_some_value(char *new_value)
{
	t_cube *c = cube();
	c->some_value = new_value;
}

int main(int argc, char **argv)
{
    ft_alloc_init();

	t_cube *cube = ft_malloc(sizeof(t_cube));
	
    cube->mlx = mlx_init();
	cube->win = mlx_new_window(cube->mlx, 800, 600, "Cub3D");
	cube->some_value = "Hello, World!";
	init_cube(cube);

	change_some_value("Hello, 42!");
	play();

    ft_destructor();
    return (0);
}