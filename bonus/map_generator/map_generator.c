/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:50:59 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/30 14:00:49 by btvildia         ###   ########.fr       */
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
			if (data->grid[y][x] == WALL_PIX)
				write(fd, "1", 1);
			else if (data->grid[y][x] == DOOR_PIX)
				write(fd, "D", 1);
			else if (data->grid[y][x] == SHOP_PIX)
				write(fd, "M", 1);
			else if (data->grid[y][x] == GENERATOR_PIX)
				write(fd, "G", 1);
			else if (data->grid[y][x] == PORTAL_PIX)
				write(fd, "P", 1);
			else
				write(fd, " ", 1);
			x++;
		}
		write(fd, "\n", 1);
		y++;
	}
	close(fd);
}

int	mouse_release_hook(int button, int x, int y, t_data *data)
{
	if (button == 1)
		data->drawing = 0;
	return (0);
}

int		selected_color = WALL_PIX;

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
			draw_cell(data, grid_x, grid_y, selected_color);
			data->grid[grid_y][grid_x] = selected_color;
		}
		else if (x >= SCREEN_WIDTH && x <= SCREEN_WIDTH + BUTTON_SIZE)
		{
			for (int i = 0; i < 6; i++)
			{
				if (y >= data->button[i].start_y && y <= data->button[i].end_y)
				{
					selected_color = data->button[i].color;
					break ;
				}
			}
		}
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
		if (grid_x >= 0 && grid_x < PIC_WIDTH && grid_y >= 0
			&& grid_y < PIC_HEIGHT)
		{
			draw_cell(data, grid_x, grid_y, selected_color);
			data->grid[grid_y][grid_x] = selected_color;
		}
		else if (x >= SCREEN_WIDTH && x <= SCREEN_WIDTH + BUTTON_SIZE)
		{
			for (int i = 0; i < 6; i++)
			{
				if (y >= data->button[i].start_y && y <= data->button[i].end_y)
				{
					selected_color = data->button[i].color;
					break ;
				}
			}
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
		grid[0][x] = WALL_PIX;
		grid[height - 1][x] = WALL_PIX;
		x++;
	}
	y = 0;
	while (y < height)
	{
		grid[y][0] = WALL_PIX;
		grid[y][width - 1] = WALL_PIX;
		y++;
	}
	return (grid);
}

void	draw_button(t_data *data, t_color_picker button)
{
	int	x;
	int	y;
	int	size;

	size = 4;
	y = 0;
	while (y < BUTTON_SIZE)
	{
		x = 0;
		while (x < BUTTON_SIZE)
		{
			if (x < size || x >= BUTTON_SIZE - size || y < size
				|| y >= BUTTON_SIZE - size)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + button.start_x,
					y + button.start_y, 0x27272a);
			else
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + button.start_x,
					y + button.start_y, button.color);
			x++;
		}
		y++;
	}
}

void	draw_color_selection(t_data *data)
{
	int	i;

	for (i = 0; i < 6; i++)
		draw_button(data, data->button[i]);
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
	draw_color_selection(data);
}

void	init_data(t_data *data)
{
	t_color_picker	*button;
	int				i;

	data->colors[0] = WALL_PIX;
	data->colors[1] = DOOR_PIX;
	data->colors[2] = SHOP_PIX;
	data->colors[3] = GENERATOR_PIX;
	data->colors[4] = PORTAL_PIX;
	data->colors[5] = EMPTY_PIX;
	button = ft_calloc(6, sizeof(t_color_picker));
	i = 0;
	while (i < 6)
	{
		button[i].color = data->colors[i];
		button[i].start_x = SCREEN_WIDTH;
		button[i].start_y = (BUTTON_SIZE * i);
		button[i].end_x = SCREEN_WIDTH + BUTTON_SIZE;
		button[i].end_y = BUTTON_SIZE * (i + 1);
		i++;
	}
	data->button = button;
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH + BUTTON_SIZE,
			SCREEN_HEIGHT, "Map_Generator");
	data.grid = get_grid(PIC_HEIGHT, PIC_WIDTH);
	init_data(&data);
	data.drawing = 0;
	clear_image(&data);
	mlx_mouse_hook(data.win_ptr, mouse_press, &data);
	mlx_hook(data.win_ptr, 6, 1L << 6, mouse_move_hook, &data);
	mlx_hook(data.win_ptr, 5, 1L << 3, mouse_release_hook, &data);
	mlx_key_hook(data.win_ptr, key_press, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
