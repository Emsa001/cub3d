/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:29:17 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 23:43:07 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	remove_string_queue(t_string **q)
{
	if (*q)
	{
		if ((*q)->str)
			(*q)->str = NULL;
		free(*q);
		*q = NULL;
	}
}

void	clear_string_queue(t_render *r)
{
	t_string	*current;
	t_string	*next;

	pthread_mutex_lock(&r->string_queue_mutex);
	current = r->string_queue;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		remove_string_queue(&current);
		current = next;
	}
	r->string_queue = NULL;
	pthread_mutex_unlock(&r->string_queue_mutex);
}

void	put_string_queue(t_render *r)
{
	t_string	*q;
	t_string	*tmp;

	pthread_mutex_lock(&r->string_queue_mutex);
	q = r->string_queue;
	while (q != NULL)
	{
		render_string(q);
		tmp = q->next;
		remove_string_queue(&q);
		q = tmp;
	}
	r->string_queue = NULL;
	pthread_mutex_unlock(&r->string_queue_mutex);
}
