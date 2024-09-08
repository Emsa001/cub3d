/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:10:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/08 21:05:46 by escura           ###   ########.fr       */
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
	c->delta_time = 1.0;
	c->buttons = NULL;
	c->paused = false;
	c->async_id = 0;
	c->add_money = 0;

	ft_memset(c->items, 0, sizeof(c->items));
	pthread_mutex_init(&c->pause_mutex, NULL);
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

    r->string_queue = NULL;
    r->image_queue = NULL;
    pthread_mutex_init(&r->string_queue_mutex, NULL);
    pthread_mutex_init(&r->image_queue_mutex, NULL);
	
	render = r;
	
	return (render);
}

t_render *render(void)
{
	return (init_render(NULL));
}
