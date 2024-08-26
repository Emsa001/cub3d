/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:38:54 by escura            #+#    #+#             */
/*   Updated: 2024/08/26 09:31:31 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "async.h"

async_queue_t	*init_async_queue(void)
{
	async_queue_t	*queue;

	queue = ft_malloc(sizeof(async_queue_t));
	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;
	return (queue);
}

async_queue_t	*get_async_queue(void)
{
	static async_queue_t	*queue = NULL;

	if (queue == NULL)
	{
		queue = init_async_queue();
		if (queue == NULL)
			return (NULL);
	}
	return (queue);
}

void	add_async(async_t async)
{
	async_queue_t	*queue;
	async_t			*new_async;

	queue = get_async_queue();
	new_async = ft_malloc(sizeof(async_t));
	*new_async = async;
	new_async->next = NULL;
	if (queue->size == 0)
	{
		queue->head = new_async;
		queue->tail = new_async;
	}
	else
	{
		queue->tail->next = new_async;
		queue->tail = new_async;
	}
	queue->size++;
}

void	remove_async(async_t *async)
{
	async_queue_t	*queue;
	async_t			*current;
	async_t			*prev;

	queue = get_async_queue();
	current = queue->head;
	prev = NULL;
	while (current)
	{
		if (current == async)
		{
			if (prev)
				prev->next = current->next;
			else
				queue->head = current->next;
			if (current == queue->tail)
				queue->tail = prev;
			ft_free(current);
			queue->size--;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	run_async_queue(void)
{
	async_queue_t	*queue;
	async_t			*current;
	async_t			*next;
	int				x;
	int				new_width;
	int				new_height;
	int				new_x;
	int				new_y;

	queue = get_async_queue();
	current = queue->head;
	next = NULL;
	x = 0;
	while (current)
	{
		next = current->next;
		if (current->time <= 0)
		{
			current->function(current->arg);
			remove_async(current);
		}
		else
		{
            int ICON_WIDTH = current->icon->width;
            int ICON_HEIGHT = current->icon->height;

			current->time -= 1;

            // printf("current->time: %d\n", current->time);

			float scale = (float)current->time / 300.0f;
            if(scale > 3.0f)
                scale = 3.0f;
			if (scale < 1.0f)
				scale = 1.0f; 
			new_width = (int)(ICON_WIDTH * scale);
			new_height = (int)(ICON_HEIGHT * scale);
			new_x = WIDTH - (100 + x) + (ICON_WIDTH - new_width) / 2;
			new_y = HEIGHT - 100 + (ICON_HEIGHT - new_height) / 2;
			put_image(current->icon, new_x, new_y, scale);
		    x += 30 * scale;
		}
		current = next;
	}
}

void	destroy_async_queue(void)
{
	async_queue_t	*queue;
	async_t			*current;
	async_t			*next;

	queue = get_async_queue();
	current = queue->head;
	next = NULL;
	while (current)
	{
		next = current->next;
		ft_free(current);
		current = next;
	}
	ft_free(queue);
}
