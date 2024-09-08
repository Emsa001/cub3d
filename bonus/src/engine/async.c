/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:38:54 by escura            #+#    #+#             */
/*   Updated: 2024/09/08 18:39:56 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void* run_process_and_function(void* arg) {
	t_async* current = (t_async*)arg;
	current->start(current);

	int sleep_time = current->time;
	int sleep_interval = 10;
	current->time_elapsed = 0;

	while (current->time_elapsed < sleep_time) {
		pthread_mutex_lock(&current->cube->pause_mutex);
		bool paused = current->cube->paused;
		pthread_mutex_unlock(&current->cube->pause_mutex);

		if (paused) {
			usleep(10 * 1000);
			continue;
		}

		current->process(current);
		current->time_elapsed += sleep_interval;
		usleep(sleep_interval * 1000);
	}

	current->end(current);
	current->cube->async_id--;
	ft_free(current); 
	return NULL;
}

void add_async(t_async* async)
{
	pthread_t thread_id;
	async->id = cube()->async_id++;
	async->cube = cube();
	async->player = player();
	async->render = render();

	pthread_create(&thread_id, NULL, run_process_and_function, async);
	pthread_detach(thread_id);
}