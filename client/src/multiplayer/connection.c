/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:51:32 by escura            #+#    #+#             */
/*   Updated: 2024/05/12 16:13:03 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "multiplayer.h"

static void server_response(int sockfd, struct sockaddr_in servaddr)
{
	static int try = 0;
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
		!= 0) {
		printf("connection with the server failed...\n");
		if (try < 5)
		{
			printf("retrying to connect to the server..\n");
			sleep(1);
			try++;
			server_response(sockfd, servaddr);
		}
		else
		{
			printf("connection with the server failed...\n");
			exit(0);
		}
	}
	else
		printf("connected to the server..\n");
}

t_server *get_server(t_server *s)
{
	static t_server *server;

	if (server == NULL)
		server = s;
	return (server);
}

void server_connect(char *ip)
{
	int sockfd;
	struct sockaddr_in servaddr;

	t_server *server = ft_malloc(sizeof(t_server));

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ip);
	servaddr.sin_port = htons(PORT);

	server->ip = ip;
	server->port = PORT;
	server->sockfd = sockfd;
	server->servaddr = servaddr;

	get_server(server);
	server_response(sockfd, servaddr);	
}

void server_disconnect()
{
	t_server *server = get_server(NULL);
	close(server->sockfd);
	printf("disconnected from the server..\n");
}