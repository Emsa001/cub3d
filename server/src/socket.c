/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:45:09 by escura            #+#    #+#             */
/*   Updated: 2024/05/13 11:47:49 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <pthread.h>

void create_socket(t_server *server)
{
    int sockfd;
    struct sockaddr_in servaddr;

    // Socket creation and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // Set up server address
    servaddr.sin_family = AF_INET;
    printf("API_URL: %s\n", API_URL);
    servaddr.sin_addr.s_addr = inet_addr(API_URL);
    servaddr.sin_port = htons(PORT);

    // Bind socket
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    } else
        printf("Socket successfully binded..\n");

    // Listen for incoming connections
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    } else
        printf("Server listening..\n");
    
    server->sockfd = sockfd;
}

void server_loop(t_server *server)
{

    struct sockaddr_in cli;
    int connfd;
    int len = sizeof(cli);
    int sockfd = server->sockfd;

    while (1) {
        connfd = accept(sockfd, (SA *)&cli, &len);
        if (connfd < 0)
        {
            printf("server accept failed...\n");
            continue;
        } else
            printf("server accept the client...\n");

        printf("Connection established\n");
        pthread_t tid;

        t_player *player = malloc(sizeof(t_player));
        t_data *data = malloc(sizeof(t_data));
        data->connfd = connfd;
        data->server = server;
        
        pthread_create(&tid, NULL, player_join, (void *)data);
    }

    close(sockfd);
}