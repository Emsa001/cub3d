/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:30:29 by escura            #+#    #+#             */
/*   Updated: 2024/10/01 12:58:12 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check(int x, int y)
{
	if (x < minimap()->last_x && y < minimap()->last_y && x > minimap()->x
		&& y > minimap()->y)
		return (1);
	else if (x < minimap()->last_x + SQUARE_SIZE && y < minimap()->last_y
		+ SQUARE_SIZE && x > minimap()->x - SQUARE_SIZE && y > minimap()->y
		- SQUARE_SIZE)
		return (2);
	return (0);
}

bool	get_c(char c, t_square *square)
{
	if (c == '1' || c == 'D' || c == 'M' || c == 'G' || c == 'P')
	{
		square->c = c;
		return (true);
	}
	return (false);
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

void	check_get(t_square *square, t_point *shape)
{
	char	c;

	c = square->c;
	if (c == 'G' || c == 'M' || c == 'P')
	{
		if (c == 'G')
		{
			shape->x /= 2;
			shape->y /= 2;
		}
		else
			shape->y /= 8;
	}
	if (c != 'G' && c != 'M' && c != 'P')
	{
		square->color = FRAME_COLOR;
		draw_top_and_bottom_borders(*square);
		draw_left_and_right_border(*square);
	}
	square->color = get_color(c);
}

void	rotate_coords(t_point p, t_player *player, t_square *square,
		t_minimap *m)
{
	float	old_bx;
	float	old_by;
	float	bx;
	float	by;

	bx = (p.x - player->x) * SQUARE_SIZE + SQUARE_SIZE / 2;
	by = (p.y - player->y) * SQUARE_SIZE + SQUARE_SIZE / 2;
	old_bx = bx;
	old_by = by;
	bx = old_bx * square->cosangle - old_by * square->sinangle;
	by = old_bx * square->sinangle + old_by * square->cosangle;
	square->x = m->center_x - SQUARE_SIZE / 2 + bx;
	square->y = m->center_y - SQUARE_SIZE / 2 + by;
}
