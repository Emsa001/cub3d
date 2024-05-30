/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:49:38 by escura            #+#    #+#             */
/*   Updated: 2024/05/16 14:19:23 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int map_get_rows(char *map)
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

static int map_get_cols(char *map)
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

void init_map(t_data *data, char *map)
{
	data->map = ft_strdup(map);
	if(!data->map)
		exit(1);

	data->mapRows = map_get_rows(data->map);
    data->mapCols = map_get_cols(data->map);
}

void init_data(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
    {
        printf("Failed to initialize mlx\n");
        exit(1);
    }

	data->player = malloc(sizeof(t_player));
    data->width = 650;
    data->height = 250;
    data->block_size = 50;
    data->win = mlx_new_window(data->mlx, data->width, data->height, "So Long");
    
    if (!data->win)
    {
        printf("Failed to create window\n");
        exit(1);
    }
}