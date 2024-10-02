/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:10:09 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 00:17:55 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cube	*cube(void)
{
	return (cube_init(NULL));
}

t_render	*render(void)
{
	return (init_render(NULL));
}

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
	c->is_special = false;
	c->levels = 4;
	c->next_portal = c->levels - 1;
	ft_memset(c->items, 0, sizeof(c->items));
	pthread_mutex_init(&c->pause_mutex, NULL);
	pthread_mutex_init(&c->add_money_mutex, NULL);
	cube = c;
	return (cube);
}

t_render	*init_render(t_render *r)
{
	static t_render	*render = NULL;

	if (r == NULL)
		return (render);
	r->mlx = mlx_init();
	if (r->mlx == NULL)
		ft_error("mlx_init() failed");
	r->win = mlx_new_window(r->mlx, WIDTH, HEIGHT, "Cub3D");
	if (r->win == NULL)
		ft_error("mlx_new_window() failed");
	r->side = 6;
	r->string_queue = NULL;
	r->image_queue = NULL;
	r->functions_queue = NULL;
	r->last_time = 0.0;
	r->frame_count = 0;
	r->fps = 0.0;
	r->fps_update_time = 0;
	r->quaility = WIDTH_SCALE;
	pthread_mutex_init(&r->string_queue_mutex, NULL);
	pthread_mutex_init(&r->image_queue_mutex, NULL);
	pthread_mutex_init(&r->functions_queue_mutex, NULL);
	pthread_mutex_init(&r->quality_mutex, NULL);
	render = r;
	return (render);
}
