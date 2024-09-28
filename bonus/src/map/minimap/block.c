/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:52:56 by escura            #+#    #+#             */
/*   Updated: 2024/09/28 21:48:37 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check(int x, int y)
{
	if (x < minimap()->last_x && y < minimap()->last_y && x > minimap()->x
		&& y > minimap()->y)
		return (true);
	return (false);
}
t_point	get_rotated_coordinates(int x, int y, float cos_theta, float sin_theta)
{
	t_point	p;
	int		translated_x;
	int		translated_y;
	int		rotated_x;
	int		rotated_y;

	p = (t_point){0, 0};
	translated_x = x - SQUARE_SIZE / 2;
	translated_y = y - SQUARE_SIZE / 2;
	rotated_x = (int)(translated_x * cos_theta - translated_y * sin_theta);
	rotated_y = (int)(translated_x * sin_theta + translated_y * cos_theta);
	p.x = SQUARE_SIZE / 2 + rotated_x;
	p.y = SQUARE_SIZE / 2 + rotated_y;
	return (p);
}

void	draw_top_and_bottom_borders(int x, int y, float angle)
{
	int		i;
	int		j;
	float	cos_theta;
	float	sin_theta;
	t_point	p;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	i = 0;
	j = 0;
	while (i < SQUARE_SIZE)
	{
		while (j < 3)
		{
			p = get_rotated_coordinates(i, j - 3, cos_theta, sin_theta);
			if (check(x + p.x, y + p.y))
				put_pixel(x + p.x, y + p.y, FRAME_COLOR, render());
			p = get_rotated_coordinates(i, SQUARE_SIZE - j + 3, cos_theta,
					sin_theta);
			if (check(x + p.x, y + p.y))
				put_pixel(x + p.x, y + p.y, FRAME_COLOR, render());
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_left_and_right_border(int x, int y, float angle)
{
	int		i;
	int		j;
	float	cos_theta;
	float	sin_theta;
	t_point	p;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	i = 0;
	j = 0;
	while (j < SQUARE_SIZE)
	{
		while (i < 3)
		{
			p = get_rotated_coordinates(i - 3, j, cos_theta, sin_theta);
			if (check(x + p.x, y + p.y))
				put_pixel(x + p.x, y + p.y, FRAME_COLOR, render());
			p = get_rotated_coordinates(SQUARE_SIZE - 1 - i + 3, j, cos_theta,
					sin_theta);
			if (check(x + p.x, y + p.y))
				put_pixel(x + p.x, y + p.y, FRAME_COLOR, render());
			i++;
		}
		i = 0;
		j++;
	}
}

int	get_color(char c)
{
	if (c == '1')
		return (BLOCK_COLOR);
	if (c == 'D')
		return (DOOR_COLOR);
	if (c == 'M')
		return (SHOP_COLOR);
	if (c == 'G')
		return (GENERATOR_COLOR);
	if (c == 'P')
		return (PORTAL_COLOR);
	return (0);
}

void	draw_block(int x, int y, float angle, int c)
{
	int		i;
	int		j;
	float	cos_theta;
	float	sin_theta;
	int		start;
	t_point	p;
	t_point	shape;

	start = 0;
	cos_theta = cos(angle);
	sin_theta = sin(angle);
	shape.x = SQUARE_SIZE;
	shape.y = SQUARE_SIZE;
	if (c == 'G' || c == 'M' || c == 'P')
	{
		if (c == 'G')
			start = shape.x / 2;
		else
			shape.y /= 8;
	}
	if (c != 'G' && c != 'M' && c != 'P')
	{
		draw_top_and_bottom_borders(x, y, angle);
		draw_left_and_right_border(x, y, angle);
	}
	i = start;
	while (i < shape.x)
	{
		j = start;
		while (j < shape.y)
		{
			p = get_rotated_coordinates(i, j, cos_theta, sin_theta);
			if (check(x + p.x, y + p.y))
				put_pixel(x + p.x, y + p.y, get_color(c), render());
			j++;
		}
		i++;
	}
}
