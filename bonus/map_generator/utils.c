/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:32:41 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/04 13:53:16 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_generator.h"

bool	check_num(t_data *data, int color)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while (y < PIC_HEIGHT)
	{
		x = 0;
		while (x < PIC_WIDTH)
		{
			if (data->grid[y][x] == color)
				count++;
			x++;
		}
		y++;
	}
	if ((color == PLAYER_PIX && count >= 1) || (color == PORTAL_PIX
			&& count >= 3) || (color == GENERATOR_PIX && count >= 20)
		|| (color == SHOP_PIX && count >= 20) || (color == DOOR_PIX
			&& count >= 20))
		return (false);
	return (true);
}

void	check_curr_color(int y, t_data *data)
{
	int	i;

	i = 0;
	while (i < MAX_COLOR)
	{
		if (y >= data->button[i].start_y && y <= data->button[i].end_y)
		{
			data->curr_color = data->button[i].color;
			break ;
		}
		i++;
	}
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
	data->colors[6] = PLAYER_PIX;
	data->curr_color = WALL_PIX;
	data->grid = get_grid(PIC_HEIGHT, PIC_WIDTH);
	data->drawing = 0;
	button = ft_calloc(MAX_COLOR, sizeof(t_color_picker));
	i = 0;
	while (i < MAX_COLOR)
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
