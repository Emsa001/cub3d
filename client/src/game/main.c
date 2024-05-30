#include "so_long.h"
#include <stdio.h>
#include "multiplayer.h"

int map_get_rows(char *map)
{
	int rows = 0;
	int i = 0;
	while(map[i] != '\0')
	{
		if(map[i] == ',')
			rows++;
		i++;
	}
	return rows;
}

int map_get_cols(char *map)
{
	int cols = 0;
	int i = 0;
	while(map[i] != '\0')
	{
		if(map[i] == ',')
			break;
		cols++;
		i++;
	}
	return cols;
}

void remove_from_map(char *map, char c)
{
	int i = 0;
	while(map[i] != '\0')
	{
		if(map[i] == c)
			map[i] = '0';
		i++;
	}
}

int	render_next_frame(t_data *data)
{
	static int frame = 0;

	frame++;
	if(frame < 1000) 
		return (0);
	char *s_data = server_receive_data();
	// name:escura;x:0;y:0;health:100;position:18;

	char **players = ft_split(s_data, '\n');
	int i = 0;
	while(players[i] != NULL)
	{
		char **player = ft_split(players[i], ';');
		int j = 0;
		char id = ' ';
		while(player[j] != NULL)
		{
			char **d = ft_split(player[j], ':');
			if(ft_strncmp(d[0], "id", 2) == 0)
				id = d[1][0];
			else if(ft_strncmp(d[0], "name", 4) == 0)
			{
				if(ft_strcmp(d[1], get_name(NULL)) == 0)
					break;
				printf("Name: %s\n", d[1]);
			}
			else if(ft_strncmp(d[0], "position", 8) == 0)
			{
				printf("Position: %s\n", d[1]);
				int current_position = ft_atoi(d[1]);
				remove_from_map(data->map, 'G');
				data->map[current_position] = 'G';
			}
			else if(ft_strncmp(d[0], "map", 3) == 0)
			{
				printf("Map: %s\n", d[1]);
				init_map(data, d[1]);
			}
			j++;
		}
		i++;
	}

	render_scene(*data);
	frame = 0;

	// data->map[current_position + data->mapCols + 1] = 'P';
	// print_game_info();
	return (0);
}

int	start_game(void)
{
	t_data data;

	// char *map = "1111111111111,10010000000C1,1000011111001,1P0011E000001,1111111111111";
	init_data(&data);

	mlx_key_hook(data.win, key_hook, &data);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);

	// render_scene(data);

	mlx_do_sync(data.mlx);
	mlx_loop(data.mlx);
	return (0);
}