/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_async.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:13:56 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 20:10:35 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_async.h"

static void	run_async_loop(t_async *current)
{
	while (1)
	{
		pthread_mutex_lock(&current->async_mutex);
		if (current->stopped || (current->time_elapsed >= current->time
				&& current->time != -1))
		{
			pthread_mutex_unlock(&current->async_mutex);
			break ;
		}
		pthread_mutex_unlock(&current->async_mutex);
		if (current->process)
			current->process(current);
		usleep(current->process_time * 1000);
		if (current->time != -1)
			current->time_elapsed += current->process_time;
	}
}

static void	*run_async(void *arg)
{
	t_async	*current;

	current = (t_async *)arg;
	if (current->start)
		current->start(current);
	run_async_loop(current);
	if (!current->stopped)
	{
		if (current->end_main)
			add_to_functions_queue(current);
		if (current->end)
			current->end(current);
	}
	remove_from_list(current);
	return (NULL);
}

void	start_async(t_async *async)
{
	pthread_t	thread_id;

	thread_id = 0;
	pthread_mutex_init(&async->async_mutex, NULL);
	add_to_list(async);
	pthread_mutex_lock(&async->async_mutex);
	async->thread_id = thread_id;
	pthread_mutex_unlock(&async->async_mutex);
	pthread_create(&thread_id, NULL, run_async, async);
	pthread_detach(thread_id);
}

void	ft_wait(int time, void (*func)(void *), void *arg)
{
	t_async	*async;

	async = new_async();
	async->time = time;
	async->end_main = func;
	async->arg = arg;
	start_async(async);
}
