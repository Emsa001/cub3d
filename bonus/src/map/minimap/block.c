/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:52:56 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 13:49:57 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	get_rotated_coordinates(int x, int y, t_square square)
{
	t_point	p;
	t_point	t_p;
	t_point	r_p;
	int		check_result;

	p = (t_point){0, 0};
	t_p.x = x - SQUARE_SIZE / 2;
	t_p.y = y - SQUARE_SIZE / 2;
	r_p.x = (int)(t_p.x * square.cosangle - t_p.y * square.sinangle);
	r_p.y = (int)(t_p.x * square.sinangle + t_p.y * square.cosangle);
	p.x = SQUARE_SIZE / 2 + r_p.x;
	p.y = SQUARE_SIZE / 2 + r_p.y;
	check_result = check(square.x + p.x, square.y + p.y);
	if (check_result)
	{
		if (check_result == 1)
			put_pixel(square.x + p.x, square.y + p.y, square.color, render());
		return (true);
	}
	return (false);
}

void	draw_top_and_bottom_borders(t_square square)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < SQUARE_SIZE)
	{
		while (j < 3)
		{
			if (!get_rotated_coordinates(i, j - 3, square)
				|| !get_rotated_coordinates(i, SQUARE_SIZE - j + 3, square))
				return ;
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_left_and_right_border(t_square square)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < SQUARE_SIZE)
	{
		while (i < 3)
		{
			if (!get_rotated_coordinates(i - 3, j, square)
				|| !get_rotated_coordinates(SQUARE_SIZE - i + 3, j, square))
				return ;
			i++;
		}
		i = 0;
		j++;
	}
}

void	draw_block(t_square square)
{
	int		i;
	int		j;
	t_point	shape;

	shape.x = SQUARE_SIZE;
	shape.y = SQUARE_SIZE;
	check_get(&square, &shape);
	i = 0;
	while (i < shape.x)
	{
		j = 0;
		while (j < shape.y)
		{
			if (!get_rotated_coordinates(i, j, square))
				return ;
			j++;
		}
		i++;
	}
}

void	draw_blocks(t_minimap *m, t_map *map, t_player *player)
{
	t_point		p;
	t_square	square;

	p.x = 0;
	p.y = 0;
	init_square(&square, -(player->angle + PI / 2));
	while (map->map[p.y] != NULL)
	{
		while (map->map[p.y][p.x] != '\0')
		{
			if (get_c(map->map[p.y][p.x], &square))
			{
				rotate_coords(p, player, &square, m);
				draw_block(square);
			}
			p.x++;
		}
		p.x = 0;
		p.y++;
	}
}
