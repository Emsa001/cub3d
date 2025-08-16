/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:15:08 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 23:20:09 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	remove_image_queue(t_image **q)
{
	if (*q)
	{
		if ((*q)->img)
			(*q)->img = NULL;
		free(*q);
		*q = NULL;
	}
}

void	clear_image_queue(t_render *r)
{
	t_image	*current;
	t_image	*next;

	pthread_mutex_lock(&r->image_queue_mutex);
	current = r->image_queue;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		remove_image_queue(&current);
		current = next;
	}
	r->image_queue = NULL;
	pthread_mutex_unlock(&r->image_queue_mutex);
}

void	put_image_queue(t_render *r)
{
	t_image	*q;
	t_image	*tmp;

	pthread_mutex_lock(&r->image_queue_mutex);
	q = r->image_queue;
	while (q != NULL)
	{
		put_image(q->img, q->x, q->y, q->size);
		tmp = q->next;
		remove_image_queue(&q);
		q = tmp;
	}
	r->image_queue = NULL;
	pthread_mutex_unlock(&r->image_queue_mutex);
}
