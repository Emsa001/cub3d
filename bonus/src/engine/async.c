/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:38:54 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 21:59:15 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_async_manager *init_async_manager() {
    t_async_manager *manager = (t_async_manager *)ft_calloc(1, sizeof(t_async_manager));
    if (manager == NULL)
        return NULL;
    pthread_mutex_init(&manager->manager_mutex, NULL);
    manager->tasks = NULL;  // Initialize the task list as empty
    return manager;
}

t_async_manager *get_async_manager() {
    static t_async_manager *manager = NULL;
    if (manager == NULL)
        manager = init_async_manager();
    return manager;
}

void add_async_task(t_async *async) {
    t_async_manager *manager = get_async_manager();

    pthread_mutex_lock(&manager->manager_mutex);  // Lock the mutex to safely modify the list

    async->next = manager->tasks;  // Insert the new task at the beginning of the list
    manager->tasks = async;  // Update the manager’s tasks to include the new task

    pthread_mutex_unlock(&manager->manager_mutex);  // Unlock the mutex after modification
}

static void run_async_loop(t_async *current) {
    bool paused;

    while (true) {
        if(!current)
            break;
        pthread_mutex_lock(&current->async_mutex);
        if (current->stopped || (current->time_elapsed >= current->time && current->time > 0)) {
            pthread_mutex_unlock(&current->async_mutex);
            break;
        }
        pthread_mutex_unlock(&current->async_mutex);

        pthread_mutex_lock(&current->cube->pause_mutex);
        paused = current->cube->paused;
        pthread_mutex_unlock(&current->cube->pause_mutex);
        if (paused) {
            usleep(10 * 1000);
            continue;
        }
        if (current->process)
            current->process(current);
        current->time_elapsed += current->process_time;
        usleep(current->process_time * 1000);
    }
}

static void *run_async(void *arg) {
    t_async *current = (t_async *)arg;

    if (current->start)
        current->start(current);

    current->time_elapsed = 0;
    run_async_loop(current);

    if (current->end)
        current->end(current);

    printf("Async task finished\n");
    pthread_mutex_destroy(&current->async_mutex);
    pthread_detach(current->thread_id);
    pthread_exit(NULL);
    ft_free(current);
    exit(0);
    return NULL;
}

void add_async(t_async *async) {
    async->cube = cube();
    async->player = player();
    async->render = render();

    pthread_mutex_init(&async->async_mutex, NULL);

    if (!async->process_time)
        async->process_time = 10;

    add_async_task(async);
    
    pthread_create(&async->thread_id, NULL, run_async, async);
    // pthread_join(async->thread_id, NULL);

    // Add the async task to the manager for tracking
}

void stop_all_async_tasks() {
    t_async_manager *manager = get_async_manager();

    pthread_mutex_lock(&manager->manager_mutex);

    t_async *current = manager->tasks;
    while (current != NULL) {
        pthread_mutex_lock(&current->async_mutex);
        current->stopped = true;
        pthread_mutex_unlock(&current->async_mutex);

        t_async *next = current->next;
        current = next;
    }

    pthread_mutex_unlock(&manager->manager_mutex);
}