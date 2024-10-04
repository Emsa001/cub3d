/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:50:59 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/04 13:52:57 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_generator.h"

int	mouse_release_hook(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		data->drawing = 0;
	return (0);
}

int	mouse_press(int button, int x, int y, t_data *data)
{
	int	grid_x;
	int	grid_y;

	if (button == 1)
	{
		data->drawing = 1;
		grid_x = x / CELL_SIZE;
		grid_y = y / CELL_SIZE;
		if (grid_x >= 1 && grid_x < PIC_WIDTH - 1 && grid_y >= 1
			&& grid_y < PIC_HEIGHT - 1)
		{
			if ((data->curr_color != WALL_PIX) && !check_num(data,
					data->curr_color))
				return (0);
			draw_cell(data, grid_x, grid_y, data->curr_color);
			data->grid[grid_y][grid_x] = data->curr_color;
		}
		else
			check_curr_color(y, data);
	}
	return (0);
}

int	mouse_move_hook(int x, int y, t_data *data)
{
	int	grid_x;
	int	grid_y;

	if (data->drawing)
	{
		grid_x = x / CELL_SIZE;
		grid_y = y / CELL_SIZE;
		if (grid_x >= 1 && grid_x < PIC_WIDTH - 1 && grid_y >= 1
			&& grid_y < PIC_HEIGHT - 1)
		{
			if ((data->curr_color != WALL_PIX) && !check_num(data,
					data->curr_color))
				return (0);
			draw_cell(data, grid_x, grid_y, data->curr_color);
			data->grid[grid_y][grid_x] = data->curr_color;
		}
		else
			check_curr_color(y, data);
	}
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		save_draw_txt(data);
		free_data(data);
		exit(0);
	}
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH + BUTTON_SIZE,
			SCREEN_HEIGHT, "Map_Generator");
	init_data(&data);
	clear_image(&data);
	mlx_mouse_hook(data.win_ptr, mouse_press, &data);
	mlx_hook(data.win_ptr, 6, 1L << 6, mouse_move_hook, &data);
	mlx_hook(data.win_ptr, 5, 1L << 3, mouse_release_hook, &data);
	mlx_key_hook(data.win_ptr, key_press, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
