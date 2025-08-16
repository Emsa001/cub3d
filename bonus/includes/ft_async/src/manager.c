/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:14:05 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 23:03:17 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_async.h"

t_async_manager	*get_manager(void)
{
	static t_async_manager	*manager = NULL;

	if (manager == NULL)
	{
		manager = (t_async_manager *)malloc(sizeof(t_async_manager));
		ft_bzero(manager, sizeof(t_async_manager));
		manager->thread_list = NULL;
		manager->thread_count = 0;
		manager->stop_all = false;
		pthread_mutex_init(&manager->manager_mutex, NULL);
		pthread_mutex_init(&manager->list_mutex, NULL);
	}
	return (manager);
}

void	destroy_manager(void)
{
	t_async_manager	*manager;

	manager = get_manager();
	stop_all_async_tasks();
	pthread_mutex_destroy(&manager->manager_mutex);
	pthread_mutex_destroy(&manager->list_mutex);
	free(manager);
	manager = NULL;
}
