/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:18:10 by escura            #+#    #+#             */
/*   Updated: 2024/05/16 14:06:00 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <pthread.h>

t_server *init_game()
{
    t_server *server = malloc(sizeof(t_server));
    server->online = 0;
    server->players = NULL;
    server->sockfd = 0;
    server->map = ft_strdup("1111111111111,10010000000C1,1000011111001,1P0011E000001,1111111111111");

    return server;
}

int main() {
    t_server *server = init_game();
    
    create_socket(server);
    server_loop(server);

    return 0;
}
