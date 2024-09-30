/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:10:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 19:29:32 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* CUBE */

t_cube	*init_cube(t_cube *c)
{
	static t_cube	*cube;
	t_render		*r;

	if (c == NULL)
		return (cube);
	c->mlx = mlx_init();
	c->keycode = D;
	r = ft_malloc(sizeof(t_render));
	r->mlx = c->mlx;
	r->side = 1;
	init_render(r);
	cube = c;
	return (cube);
}

t_cube	*cube(void)
{
	return (init_cube(NULL));
}

t_render	*init_render(t_render *r)
{
	static t_render	*render;

	if (r == NULL)
		return (render);
	render = r;
	return (render);
}

t_render	*render(void)
{
	return (init_render(NULL));
}
