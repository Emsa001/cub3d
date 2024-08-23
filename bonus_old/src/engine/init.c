/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:10:09 by escura            #+#    #+#             */
/*   Updated: 2024/08/13 11:47:01 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* CUBE */

t_cube	*cube_init(t_cube *c)
{
	static t_cube	*cube;
	
	if (c == NULL)
		return (cube);

	c->keycode = D;
	cube = c;
	return (cube);
}

t_cube	*cube(void)
{
	return (cube_init(NULL));
}

t_render *init_render(t_render *r)
{
	static t_render	*render;

	if (r == NULL)
		return (render);

	r->mlx = mlx_init();
	r->win = mlx_new_window(r->mlx, WIDTH, HEIGHT, "Cub3D");
	r->side = 6;
	render = r;
	
	return (render);
}

t_render *render(void)
{
	return (init_render(NULL));
}
