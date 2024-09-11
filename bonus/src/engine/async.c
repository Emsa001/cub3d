/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:38:54 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 14:57:11 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	run_async_oop(t_async *current)
{
	bool		paused;

	while ((current->time_elapsed <= current->time) || current->time == -1)
	{
		pthread_mutex_lock(&current->cube->pause_mutex);
		paused = current->cube->paused;
		pthread_mutex_unlock(&current->cube->pause_mutex);
		if (paused)
		{
			usleep(10 * 1000);
			continue ;
		}
		if (current->process)
			current->process(current);
		current->time_elapsed += current->process_time;
		usleep(current->process_time * 1000);
	}
}

static void	*run_async(void *arg)
{
	t_async	*current;

	current = (t_async *)arg;
	if (current->start)
		current->start(current);
	current->time_elapsed = 0;
	run_async_oop(current);
	if (current->end)
		current->end(current);
	current->cube->async_id--;
	ft_free(current);
	return (NULL);
}

void	add_async(t_async *async)
{
	pthread_t	thread_id;

	async->id = cube()->async_id++;
	async->cube = cube();
	async->player = player();
	async->render = render();
	if(!async->process_time)
		async->process_time = 10;
	pthread_create(&thread_id, NULL, run_async, async);
	pthread_detach(thread_id);
}
