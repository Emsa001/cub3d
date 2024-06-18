/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:10:09 by escura            #+#    #+#             */
/*   Updated: 2024/06/18 17:37:10 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* CUBE */

t_cube	*init_cube(t_cube *c)
{
	static t_cube	*cube;
	
	if (c == NULL)
		return (cube);

	c->mlx = mlx_init();
	c->keycode = D;

	cube = c;
	return (cube);
}

t_cube	*cube(void)
{
	return (init_cube(NULL));
}

/* PLAYER */

t_player	*init_player(t_player *p)
{
	static t_player	*player;

	if (p == NULL)
		return (player);
	player = p;

	return (player);
}

t_player	*player(void)
{
	return (init_player(NULL));
}
