/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:53:05 by escura            #+#    #+#             */
/*   Updated: 2024/09/15 14:37:42 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"

// void add_to_functions_queue(void (*func)(void *), t_render *r)
// {
//     pthread_mutex_lock(&r->functions_queue_mutex);

//     t_functions *new = ft_calloc(sizeof(t_functions),1);
//     t_functions *tmp = r->functions_queue;

//     new->func = func;
//     new->next = NULL;

//     if (tmp == NULL)
//     {
//         r->functions_queue = new;
//         pthread_mutex_unlock(&r->functions_queue_mutex);
//         return;
//     }

//     while (tmp->next != NULL)
//         tmp = tmp->next;
//     tmp->next = new;

//     pthread_mutex_unlock(&r->functions_queue_mutex);
// }

// void execute_functions_queue(t_render *r)
// {
//     pthread_mutex_lock(&r->functions_queue_mutex);

//     t_functions *tmp = r->functions_queue;
//     t_functions *next = NULL;

//     while (tmp != NULL)
//     {
//         next = tmp->next;
//         tmp->func(NULL);
//         ft_free(tmp);
//         tmp = next;
//     }
//     r->functions_queue = NULL;

//     pthread_mutex_unlock(&r->functions_queue_mutex);
// }