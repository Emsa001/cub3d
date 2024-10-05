/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_async.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:11:07 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 15:17:33 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ASYNC_H
# define FT_ASYNC_H

# include "../../cub3d.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <unistd.h>

typedef struct s_cube			t_cube;
typedef struct s_render			t_render;
typedef struct s_player			t_player;

typedef struct s_async_manager	t_async_manager;

typedef struct s_async
{
	int							id;
	pthread_t					thread_id;
	pthread_mutex_t				async_mutex;
	t_async_manager				*manager;

	void						(*start)(struct s_async *);
	void						(*process)(struct s_async *);
	void						(*end)(struct s_async *);
	void						(*end_main)(void *arg);
	void						*arg;

	int							time;
	int							time_elapsed;
	int							process_time;
	bool						stopped;
	int 						frame;


	t_cube						*cube;
	t_render					*render;
	t_player					*player;

}								t_async;

typedef struct s_async_list
{
	t_async						*current;
	struct s_async_list			*next;
}								t_async_list;

typedef struct s_function
{
	void						(*func)(void *);
	void						*arg;
	struct s_function			*next;
}								t_function;

typedef struct s_async_manager
{
	t_function					*functions_queue;
	pthread_mutex_t				functions_queue_mutex;

	pthread_mutex_t				manager_mutex;
	pthread_mutex_t				list_mutex;

	t_async_list				*thread_list;
	int							thread_count;
	bool						stop_all;
}								t_async_manager;

void							add_to_functions_queue(t_async *async);
void							add_to_list(t_async *async);

t_async_manager					*get_manager(void);
void							destroy_manager(void);

t_async							*new_async(void);

void							remove_from_list(t_async *async);
void							start_async(t_async *async);
void							stop_all_async_tasks(void);
void							async_queue(void);
void							ft_wait(int time, void (*func)(void *),
									void *arg);

#endif