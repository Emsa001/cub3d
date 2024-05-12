/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:06:42 by escura            #+#    #+#             */
/*   Updated: 2024/05/12 20:43:56 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include "./libft/libft.h"

#define API_URL "127.0.0.1"
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

typedef struct s_player t_player;

typedef struct s_server {
    int sockfd;
    int online;
    t_player *players;
} t_server;

typedef struct s_player {
    char *name;
    int x;
    int y;
    int health;
    int position;
    struct s_player *next;
} t_player;

typedef struct s_data {
    t_server *server;
    int connfd;
} t_data;

#endif