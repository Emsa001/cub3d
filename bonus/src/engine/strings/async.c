/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:28:59 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 18:47:43 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	string_blink(t_async *async, t_string *str)
{
	if (str->blink && str->blink > -1)
	{
		async->frame++;
		if (async->frame > 2 * str->blink)
			async->frame = 0;
		return (async->frame > str->blink);
	}
	return (false);
}

static bool	string_animation(t_async *async, t_string *str, t_string *new)
{
	if (str->animation && str->animation > -1
		&& ft_strlen(str->str) > str->char_index)
	{
		new->str = ft_strdup(str->str);
		new->str[str->char_index] = '\0';
		async->frame++;
		if (async->frame > str->animation)
		{
			str->char_index++;
			async->frame = 0;
		}
	}
	if (str->char_index == str->length)
	{
		if (string_blink(async, str))
			return (true);
	}
	return (false);
}

void	enqueue_string(t_async *async)
{
	t_string		*q;
	t_render *const	r = render();
	t_string *const	str = (t_string *)async->arg;
	t_string *const	new = malloc(sizeof(t_string));

	ft_memcpy(new, str, sizeof(t_string));
	if (string_animation(async, str, new))
		return (free(new));
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
	t_string *const	str_copy = copy_string(str);

	async->process = &enqueue_string;
	async->end = end_string;
	async->arg = str_copy;
	async->process_time = 5;
	async->time = str->time;
	start_async(async);
}
