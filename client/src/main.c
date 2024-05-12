/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:08:07 by escura            #+#    #+#             */
/*   Updated: 2024/05/12 21:13:05 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *get_name(char *name)
{
	static char *n; 
	if(name != NULL)
		n = name;
		
	return n;
}

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("Singleplayer\n");
		exit(1);
	}

	printf("Multiplayer\n");
	char *ip = argv[1];

	server_connect(ip);

	// Game loop

	char *name = argv[2];

	char *data = ft_strjoin("name:", name);
	data = ft_strjoin(data, ";position:43");
	get_name(name);
	server_send_data(data);
	// server_send_data("name:Pabeckha;health:100;x:1;y:0");
	// server_send_data("name:Ellen;health:100;x:0;y:1");

	start_game();

	// while(1)
	// {
	// 	server_receive_data();
	// 	print_game_info();
	// 	// Game logic
	// 	usleep(100000);
	// }

	server_disconnect();
	return 0;
}
