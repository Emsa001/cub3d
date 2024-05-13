/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:45:07 by escura            #+#    #+#             */
/*   Updated: 2024/05/13 11:51:47 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Define a function to handle client requests
void *player_join(void *arg)
{
    t_data *data = (t_data *)arg;
    t_server *server = data->server;
    int connfd = data->connfd;
    printf("Connection established 2\n");
    char buff[MAX];
    ssize_t n;

    server->online++;

    while ((n = read(connfd, buff, sizeof(buff) - 1)) > 0) {
        buff[n] = '\0';

        if(strcmp(buff, "get_data") == 0)
        {
            send_data(data);
            continue;
        }

        printf("Received: %s\n", buff);

        if (server->players == NULL) {
            server->players = malloc(sizeof(t_player));
            server->players->name = NULL;
            server->players->next = NULL;
        }
        save_data(server->players, buff);
        write(connfd, "saved!\n", 7);
    }

    server->online--;

    close(connfd);
    free(arg);
    pthread_exit(NULL);
}
