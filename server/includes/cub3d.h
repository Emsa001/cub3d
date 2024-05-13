/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:06:42 by escura            #+#    #+#             */
/*   Updated: 2024/05/13 11:52:24 by escura           ###   ########.fr       */
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

#define API_URL "10.12.9.6"
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

/* sockets */
void create_socket(t_server *server);
void server_loop(t_server *server);

/* player */
void *player_join(void *arg);

/* data */
char *get_all_players_data(t_server *server);
void send_data(t_data *data);
void save_data(t_player *player, char *buff);

#endif