/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:08:59 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 21:06:59 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_cube	t_cube;
typedef struct s_player	t_player;
typedef struct s_render	t_render;

typedef struct s_async
{
	void				(*start)(struct s_async *);
	void				(*process)(struct s_async *);
	void				(*end)(struct s_async *);
	void				*arg;

	int					time;
	int					time_elapsed;
	int					process_time;
	bool				stopped;

	t_cube				*cube;
	t_player			*player;
	t_render			*render;

    pthread_mutex_t async_mutex;
	pthread_t thread_id;  // Add this field to store the thread ID
	struct s_async *next; // Pointer to the next async task in the linked list
}						t_async;

typedef struct s_async_manager
{
	t_async *tasks;                // Head of the linked list of async tasks
	pthread_mutex_t manager_mutex; // Mutex to safely modify the list of tasks
}						t_async_manager;

void					add_async(t_async *async);
void					stop_all_async_tasks(void);