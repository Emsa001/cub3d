/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:50:59 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/26 18:45:46 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_generator.h"

void	draw_cell(t_data *data, int x, int y, int color)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = x * CELL_SIZE;
	start_y = y * CELL_SIZE;
	i = 0;
	j = 0;
	while (i < CELL_SIZE)
	{
		j = 0;
		while (j < CELL_SIZE)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, start_x + i, start_y
				+ j, color);
			j++;
		}
		i++;
	}
}

void	save_draw_txt(t_data *data)
{
	int	fd;
	int	x;
	int	y;

	fd = open("../maps/map.cub", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	x = 0;
	y = 0;
	while (y < PIC_HEIGHT) 
	{
		x = 0;
		while (x < PIC_WIDTH)
		{
			if (data->grid[y][x] == 0xFFFFFF)
				write(fd, "1", 1);
			else
				write(fd, " ", 1);
			x++;
		}
		write(fd, "\n", 1);
		y++;
	}
	close(fd);
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
		if (grid_x >= 0 && grid_x < PIC_WIDTH && grid_y >= 0
			&& grid_y < PIC_HEIGHT)
		{
			draw_cell(data, grid_x, grid_y, 0xFFFFFF);
			data->grid[grid_y][grid_x] = 0xFFFFFF;
		}
	}
	return (0);
}

int	mouse_release_hook(int button, int x, int y, t_data *data)
{
	if (button == 1)
		data->drawing = 0;
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
		if (grid_x >= 0 && grid_x < PIC_WIDTH && grid_y >= 0
			&& grid_y < PIC_HEIGHT)
		{
			draw_cell(data, grid_x, grid_y, 0xFFFFFF);
			data->grid[grid_y][grid_x] = 0xFFFFFF;
		}
	}
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < PIC_HEIGHT)
	{
		ft_free(data->grid[i]);
		i++;
	}
	ft_free(data->grid);
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

void	clear_image(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < PIC_HEIGHT)
	{
		x = 0;
		while (x < PIC_WIDTH)
		{
			draw_cell(data, x, y, data->grid[y][x]);
			x++;
		}
		y++;
	}
}

int	**get_grid(int height, int width)
{
	int	**grid;
	int	x;
	int	y;

	grid = ft_calloc(height, sizeof(int *));
	x = 0;
	y = 0;
	while (y < height)
		grid[y++] = ft_calloc(width, sizeof(int));
	x = 0;
	while (x < width)
	{
		grid[0][x] = 0xFFFFFF;
		grid[height - 1][x] = 0xFFFFFF;
		x++;
	}
	y = 0;
	while (y < height)
	{
		grid[y][0] = 0xFFFFFF;
		grid[y][width - 1] = 0xFFFFFF;
		y++;
	}
	return (grid);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Map_Generator");
	data.grid = get_grid(PIC_HEIGHT, PIC_WIDTH);
	data.drawing = 0;
	clear_image(&data);
	mlx_mouse_hook(data.win_ptr, mouse_press, &data);
	mlx_hook(data.win_ptr, 6, 1L << 6, mouse_move_hook, &data);
	mlx_hook(data.win_ptr, 5, 1L << 3, mouse_release_hook, &data);
	mlx_key_hook(data.win_ptr, key_press, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
