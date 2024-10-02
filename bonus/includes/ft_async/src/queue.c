/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:13:59 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 23:03:26 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_async.h"

void	add_to_functions_queue(t_async *async)
{
	t_async_manager	*manager;
	t_function		*new;
	t_function		*tmp;

	manager = get_manager();
	pthread_mutex_lock(&manager->functions_queue_mutex);
	new = (t_function *)malloc(sizeof(t_function));
	tmp = manager->functions_queue;
	new->func = async->end_main;
	new->arg = async->arg;
	new->next = NULL;
	if (tmp == NULL)
	{
		manager->functions_queue = new;
		pthread_mutex_unlock(&manager->functions_queue_mutex);
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	pthread_mutex_unlock(&manager->functions_queue_mutex);
}

void	async_queue(void)
{
	t_async_manager	*manager;
	t_function		*tmp;
	t_function		*next;

	manager = get_manager();
	pthread_mutex_lock(&manager->functions_queue_mutex);
	tmp = manager->functions_queue;
	next = NULL;
	while (tmp != NULL)
	{
		next = tmp->next;
		tmp->func(tmp->arg);
		free(tmp);
		tmp = next;
	}
	manager->functions_queue = NULL;
	pthread_mutex_unlock(&manager->functions_queue_mutex);
}
