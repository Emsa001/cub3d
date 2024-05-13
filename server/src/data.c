/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:48:32 by escura            #+#    #+#             */
/*   Updated: 2024/05/13 11:53:39 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *get_all_players_data(t_server *server)
{
    t_player *original_player = server->players;
    t_player *player = server->players;
    char *data = ft_strdup("");

    while (player->next != NULL) {
        char *temp = ft_strjoin("name:", player->name);
        char *temp2 = ft_strjoin(temp, ";");
        temp = ft_strjoin(temp2, "x:");
        temp2 = ft_strjoin(temp, ft_itoa(player->x));
        temp = ft_strjoin(temp2, ";");
        temp2 = ft_strjoin(temp, "y:");
        temp = ft_strjoin(temp2, ft_itoa(player->y));
        temp2 = ft_strjoin(temp, ";");
        temp = ft_strjoin(temp2, "health:");
        temp2 = ft_strjoin(temp, ft_itoa(player->health));
        temp = ft_strjoin(temp2, ";");
        temp2 = ft_strjoin(temp, "position:");
        temp = ft_strjoin(temp2, ft_itoa(player->position));
        temp2 = ft_strjoin(temp, ";");

        char *temp_data = ft_strjoin(data, temp2);
        data = temp_data;
        
        player = player->next;
    }

    server->players = original_player;

    return data;
}

void send_data(t_data *data)
{

    char *online_str = ft_itoa(data->server->online);
    char *temp = ft_strjoin("online:", online_str);
    char *msg = ft_strjoin(temp, "\n");

    char *players_data = get_all_players_data(data->server);

    write(data->connfd, players_data, ft_strlen(players_data) + 1);
}


void save_data(t_player *player, char *buff)
{
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
