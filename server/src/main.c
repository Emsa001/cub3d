/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:18:10 by escura            #+#    #+#             */
/*   Updated: 2024/05/12 20:48:34 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <pthread.h>

char *get_all_players_data(t_server *server) {
    t_player *original_player = server->players;
    t_player *player = server->players;  // Make a copy of the pointer
    char *data = ft_strdup("");

    while (player->next != NULL) {
        char *temp = ft_strjoin("name:", player->name);
        char *temp2 = ft_strjoin(temp, ";");
        free(temp);
        temp = ft_strjoin(temp2, "x:");
        free(temp2);
        temp2 = ft_strjoin(temp, ft_itoa(player->x));
        free(temp);
        temp = ft_strjoin(temp2, ";");
        free(temp2);
        temp2 = ft_strjoin(temp, "y:");
        free(temp);
        temp = ft_strjoin(temp2, ft_itoa(player->y));
        free(temp2);
        temp2 = ft_strjoin(temp, ";");
        free(temp);
        temp = ft_strjoin(temp2, "health:");
        free(temp2);
        temp2 = ft_strjoin(temp, ft_itoa(player->health));
        free(temp);
        temp = ft_strjoin(temp2, ";");
        free(temp2);
        temp2 = ft_strjoin(temp, "position:");
        free(temp);
        temp = ft_strjoin(temp2, ft_itoa(player->position));
        free(temp2);
        temp2 = ft_strjoin(temp, ";");
        free(temp);

        // Concatenate temp2 with data
        char *temp_data = ft_strjoin(data, temp2);
        free(data);
        data = temp_data;
        
        player = player->next;
    }

    server->players = original_player;


    return data;
}



// Function to send data to all connected clients
void send_data_to_clients(t_data *data) {

    char *online_str = ft_itoa(data->server->online);
    char *temp = ft_strjoin("online:", online_str);
    char *msg = ft_strjoin(temp, "\n");

    char *players_data = get_all_players_data(data->server);

    write(data->connfd, players_data, ft_strlen(players_data) + 1);
}

void save_data(t_player *player, char *buff) {
    char **data = ft_split(buff, ';');
    int i = 0;

    while (data[i]) {
        char **temp = ft_split(data[i], ':');
        char *name = ft_strdup(temp[0]); // Allocate memory for name
        char *value = ft_strdup(temp[1]); // Allocate memory for value

        if (strcmp(name, "name") == 0)
            player->name = value;
        else if (strcmp(name, "x") == 0)
            player->x = ft_atoi(value);
        else if (strcmp(name, "y") == 0)
            player->y = ft_atoi(value);
        else if (strcmp(name, "health") == 0)
            player->health = ft_atoi(value);
        else if (strcmp(name, "position") == 0)
            player->position = ft_atoi(value);

        i++;
    }

    if (player->next == NULL) {
        player->next = malloc(sizeof(t_player));
        player->next->name = NULL;
        player->next->next = NULL;
    }
}


// Define a function to handle client requests
void *handle_client(void *arg) {
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
            send_data_to_clients(data);
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

t_server *init_game()
{
    t_server *server = malloc(sizeof(t_server));
    server->online = 0;
    server->players = NULL;
    server->sockfd = 0;

    return server;
}

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

int main() {
    t_server *server = init_game();
    create_socket(server);

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
        
        pthread_create(&tid, NULL, handle_client, (void *)data);
    }

    close(sockfd);
    return 0;
}
