/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:14:48 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 23:23:01 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	enqueue_image(t_async *async)
{
	t_image *const	img = (t_image *)async->arg;
	t_render *const	r = render();
	t_image *const	new = malloc(sizeof(t_image));
	t_image			*q;

	if (!new)
		return ;
	new->img = img->img;
	new->x = img->x;
	new->y = img->y;
	new->size = img->size;
	new->time = img->time;
	new->next = NULL;
	pthread_mutex_lock(&r->image_queue_mutex);
	if (!r->image_queue)
		r->image_queue = new;
	else
	{
		q = r->image_queue;
		while (q->next)
			q = q->next;
		q->next = new;
	}
	pthread_mutex_unlock(&r->image_queue_mutex);
}

static void	end_image(t_async *async)
{
	t_image *const	img = (t_image *)async->arg;

	if (img)
	{
		if (img->img)
			img->img = NULL;
		ft_free(img);
	}
}

void	render_image_async(t_image *img)
{
	t_async *const	async = new_async();
	t_image *const	img_copy = ft_malloc(sizeof(t_image));

	img_copy->img = img->img;
	img_copy->x = img->x;
	img_copy->y = img->y;
	img_copy->size = img->size;
	img_copy->time = img->time;
	img_copy->next = NULL;
	async->process = &enqueue_image;
	async->end = &end_image;
	async->arg = img_copy;
	async->process_time = 5;
	async->time = img->time;
	start_async(async);
}
