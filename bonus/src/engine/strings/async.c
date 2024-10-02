/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:28:59 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 23:40:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	enqueue_string(t_async *async)
{
	t_string		*q;
	t_render *const	r = render();
	t_string *const	str = (t_string *)async->arg;
	t_string *const	new = malloc(sizeof(t_string));

	ft_memcpy(new, str, sizeof(t_string));
	new->next = NULL;
	pthread_mutex_lock(&r->string_queue_mutex);
	if (!r->string_queue)
		r->string_queue = new;
	else
	{
		q = r->string_queue;
		while (q->next)
			q = q->next;
		q->next = new;
	}
	pthread_mutex_unlock(&r->string_queue_mutex);
}

void	end_string(t_async *async)
{
	t_string *const	str = (t_string *)async->arg;

	if (str)
	{
		if (str->str)
			str->str = NULL;
		ft_free(str);
	}
}

void	render_string_async(t_string *str)
{
	t_async *const	async = new_async();
	t_string *const	str_copy = ft_malloc(sizeof(t_string));

	str_copy->str = ft_strdup(str->str);
	str_copy->x = str->x;
	str_copy->y = str->y;
	str_copy->color = str->color;
	str_copy->size = str->size;
	str_copy->time = str->time;
	str_copy->background = str->background;
	str_copy->padding = str->padding;
	str_copy->next = NULL;
	ft_free(str->str);
	async->process = &enqueue_string;
	async->end = end_string;
	async->arg = str_copy;
	async->process_time = 5;
	async->time = str->time;
	start_async(async);
}
