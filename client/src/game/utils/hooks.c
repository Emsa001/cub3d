/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:34:46 by escura            #+#    #+#             */
/*   Updated: 2024/05/12 21:15:48 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "multiplayer.h"

int	key_hook(int keycode, t_data *data)
{
	// printf("You've pressed: %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
    
	int current_position = find_position(data->map, 'P');
	if(find_position(data->map, 'E') == -1)
		return 0;

	if(keycode == 100){
		int right_element = data->map[current_position + 1];
		if(right_element != '1'){
			data->map[current_position + 1] = 'P';
			data->map[current_position] = '0';
			data->player_direction = 0;
			render_scene(*data);
		}
	}

	if(keycode == 97){
		int left_element = data->map[current_position - 1];
		if(left_element != '1'){
			data->map[current_position - 1] = 'P';
			data->map[current_position] = '0';
			data->player_direction = 1;
			render_scene(*data);
		}
	}

	if(keycode == 119){
		int top_element = data->map[current_position - (data->mapCols) - 1];
		if(top_element != '1'){
			data->map[current_position - data->mapCols - 1] = 'P';
			data->map[current_position] = '0';
			render_scene(*data);
		}
	}

	if(keycode == 115){
		int down_element = data->map[current_position + (data->mapCols) + 1];
		if(down_element != '1'){
			data->map[current_position + data->mapCols + 1] = 'P';
			data->map[current_position] = '0';
			render_scene(*data);
		}
	}

	char *position = ft_itoa(find_position(data->map, 'P'));

	char *temp = ft_strjoin("name:", get_name(NULL));
	temp = ft_strjoin(temp, ";position:");
	char *data_to_send = ft_strjoin(temp, position);
	server_send_data(data_to_send);

	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	// printf("You've pressed: %d\n", button);
	// printf("Mouse position: %d, %d\n", x, y);
	return (0);
}
