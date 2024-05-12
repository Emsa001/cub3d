/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:10:01 by escura            #+#    #+#             */
/*   Updated: 2024/05/12 21:16:04 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "multiplayer.h"

void server_send_data(char *data)
{
    const t_server *server = get_server(NULL);
    int sockfd = server->sockfd;

    char buff[MAX];
    bzero(buff, sizeof(buff));
    strncpy(buff, data, sizeof(buff) - 1);
    write(sockfd, buff, strlen(buff));
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    // printf("From Server: %s", buff);
}

char *server_receive_data()
{
    const t_server *server = get_server(NULL);
    int sockfd = server->sockfd;

    char buff[1024];
    write(sockfd, "get_data", 8);
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));

    return ft_strdup(buff);
    // printf("From Server: %s", buff);
}

void print_game_info(){
    const t_server *server = get_server(NULL);

    // printf("Online: %d\n", server->online);
}