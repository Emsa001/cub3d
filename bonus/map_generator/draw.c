/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:41:37 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/04 20:04:33 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_generator.h"

void	draw_cell(t_data *data, int x, int y, int color)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = x * (SCREEN_WIDTH / PIC_WIDTH);
	start_y = y * (SCREEN_WIDTH / PIC_WIDTH);
	i = 0;
	j = 0;
	while (i < (SCREEN_WIDTH / PIC_WIDTH))
	{
		j = 0;
		while (j < (SCREEN_WIDTH / PIC_WIDTH))
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, start_x + i, start_y
				+ j, color);
			j++;
		}
		i++;
	}
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

void	clear_image(t_data *data)
{
	int	x;
	int	y;
	int	i;

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
	i = 0;
	while (i < MAX_COLOR)
	{
		draw_button(data, data->button[i]);
		i++;
	}
}

void	write_in_file(int color, int fd)
{
	if (color == WALL_PIX)
		write(fd, "1", 1);
	else if (color == DOOR_PIX)
		write(fd, "D", 1);
	else if (color == SHOP_PIX)
		write(fd, "M", 1);
	else if (color == GENERATOR_PIX)
		write(fd, "G", 1);
	else if (color == PORTAL_PIX)
		write(fd, "P", 1);
	else if (color == PLAYER_PIX)
		write(fd, "N", 1);
	else
		write(fd, " ", 1);
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
			write_in_file(data->grid[y][x], fd);
			x++;
		}
		write(fd, "\n", 1);
		y++;
	}
	close(fd);
}
