/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:37:26 by escura            #+#    #+#             */
/*   Updated: 2024/09/07 12:43:56 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASYNC_H
# define ASYNC_H

# include "cub3d.h"
# include "textures.h"

typedef struct async_s
{
    void (*function)(void *);
    void *arg;
    int time;
    t_texture *icon;
    struct async_s *next;
} async_t;

typedef struct async_queue_s
{
    async_t *head;
    async_t *tail;
    int size;
} async_queue_t;


async_queue_t *init_async_queue();
async_queue_t *get_async_queue();
void  add_async(async_t async);
void run_async_queue();
void destroy_async_queue();

#endif