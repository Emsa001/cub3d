/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplayer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:52:33 by escura            #+#    #+#             */
/*   Updated: 2024/05/13 11:41:43 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIPLAYER_H
# define MULTIPLAYER_H

#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

typedef struct s_server
{
    char    *ip;
    int     port;
    int     sockfd;
    struct  sockaddr_in servaddr;
    struct  sockaddr_in cli;
    int     online;
}               t_server;


/* Connection */
void server_connect(char *ip);
void server_disconnect();

/* Data */
t_server *get_server(t_server *s);
void server_send_data(char *data);
char *server_receive_data();
char *get_name(char *name);


/* Players data */

typedef struct s_players
{
    int     id;
    char    *name;
    int     health;
    int     armor;
    int     ammo;
    int     position[2];
}               t_player;

#endif