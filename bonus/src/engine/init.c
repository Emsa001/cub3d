/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:10:09 by escura            #+#    #+#             */
/*   Updated: 2024/09/25 14:05:13 by btvildia         ###   ########.fr       */
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
	c->is_special = false;
    c->levels = 4;
    c->next_portal = 2;

	ft_memset(c->items, 0, sizeof(c->items));
	pthread_mutex_init(&c->pause_mutex, NULL);
	pthread_mutex_init(&c->add_money_mutex, NULL);    
	cube = c;
	return (cube);
}

t_cube	*cube(void)
{
	return (cube_init(NULL));
}

t_render *init_render(t_render *r)
{
    static t_render *render = NULL;

    if (r == NULL)
        return (render);

    // Initialize members of the t_render structure
    r->mlx = mlx_init();
    if (r->mlx == NULL) {
        return NULL;
    }

    r->win = mlx_new_window(r->mlx, WIDTH, HEIGHT, "Cub3D");
    if (r->win == NULL) {
        return NULL;
    }

    // Initialize additional members
    r->side = 6;

    r->string_queue = NULL;  // Make sure this is properly initialized
    r->image_queue = NULL;   // Make sure this is properly initialized
    r->functions_queue = NULL; // Make sure this is properly initialized

    // Initialize mutexes
    pthread_mutex_init(&r->string_queue_mutex, NULL);
    pthread_mutex_init(&r->image_queue_mutex, NULL);
    pthread_mutex_init(&r->put_pixel_mutex, NULL);
    pthread_mutex_init(&r->functions_queue_mutex, NULL);


    // Assign the static variable
    render = r;
    
    return (render);
}


t_render *render(void)
{
	return (init_render(NULL));
}
