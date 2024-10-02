/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_async.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:14:01 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 23:02:59 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_async.h"

// Add async task to the list
void	add_to_list(t_async *async)
{
	t_async_manager	*manager;
	t_async_list	*node;
	t_async_list	*new_node;

	manager = async->manager;
	pthread_mutex_lock(&manager->list_mutex);
	node = manager->thread_list;
	new_node = (t_async_list *)malloc(sizeof(t_async_list));
	new_node->current = async;
	new_node->next = NULL;
	if (node == NULL)
		manager->thread_list = new_node;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new_node;
	}
	pthread_mutex_unlock(&manager->list_mutex);
	pthread_mutex_lock(&manager->manager_mutex);
	pthread_mutex_lock(&async->async_mutex);
	async->id = manager->thread_count;
	pthread_mutex_unlock(&async->async_mutex);
	manager->thread_count++;
	pthread_mutex_unlock(&manager->manager_mutex);
}

t_async	*new_async(void)
{
	t_async_manager	*manager;
	t_async			*async;

	manager = get_manager();
	async = (t_async *)malloc(sizeof(t_async));
	ft_bzero(async, sizeof(t_async));
	async->id = -1;
	async->manager = manager;
	async->start = NULL;
	async->process = NULL;
	async->end = NULL;
	async->end_main = NULL;
	async->arg = NULL;
	async->time = 10 * 1000;
	async->time_elapsed = 0;
	async->process_time = 100;
	async->stopped = false;
	async->cube = cube();
	async->render = render();
	async->player = player();
	return (async);
}
