/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:48:32 by escura            #+#    #+#             */
/*   Updated: 2024/05/16 15:03:04 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *get_all_players_data(t_server *server)
{
    t_player *original_player = server->players;
    t_player *player = server->players;
    char *data = ft_strdup("");

    while (player->next != NULL) {
        char *id = ft_strdup("id:");
        id = add_char(id, player->id);
        id = add_char(id, ';');

        char *temp = ft_strjoin(data, id);
        // temp2 = ft_strjoin(temp, "position:");
        // temp = ft_strjoin(temp2, ft_itoa(player->position));
        // temp2 = ft_strjoin(temp, ";");

        // char *temp_data = ft_strjoin(data, temp2);
        // data = temp_data;
        
        player = player->next;
    }

    server->players = original_player;
    printf("Data: %s\n", data);
    return data;
}

void send_data(t_data *data)
{
    char *players_data = get_all_players_data(data->server);
    char *map = ft_strjoin("map:", data->server->map);
    char *x = ft_strjoin(map, ";");
    char *data_to_send = ft_strjoin(x, players_data);

    write(data->connfd, data_to_send, ft_strlen(data_to_send) + 1);
}

int find_position(char *map, char c)
{
	int i = 0;
	while(map[i] != '\0')
	{
		if(map[i] == c)
			return i;
		i++;
	}
	return -1;
}

void save_data(t_player *player, char *buff, t_server *server)
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
        else if (strcmp(name, "position") == 0){
            if(player->position > 0)
                server->map[player->position] = '0';
            player->position = ft_atoi(value);
            if(player->position > 0)
                server->map[player->position] = player->id;
        }
        i++;
    }

    if (player->next == NULL) {
        player->next = malloc(sizeof(t_player));
        player->next->name = NULL;
        player->next->next = NULL;
    }
}
