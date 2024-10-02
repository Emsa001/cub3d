/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:38:02 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/02 21:26:58 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_side(int x, int y, char **map)
{
	if (map[y][x - 1] == '1')
		return (1);
	else if (map[y - 1][x] == '1')
		return (2);
	else if (map[y][x + 1] == '1')
		return (3);
	else if (map[y + 1][x] == '1')
		return (4);
	return (0);
}

void	terminate_blocks(t_block **blocks, int i)
{
	(*blocks)[i].x = -1;
	(*blocks)[i].y = -1;
	(*blocks)[i].id = -1;
	(*blocks)[i].s_x = -1;
	(*blocks)[i].s_y = -1;
	(*blocks)[i].type = '\0';
}

void	init_once(t_block *blocks, t_float point, int *k, char type)
{
	blocks[*k].s_x = point.x;
	blocks[*k].s_y = point.y - 0.02;
	blocks[*k].x = point.x;
	blocks[*k].y = point.y - 0.02;
	blocks[*k].id = *k;
	blocks[*k].type = type;
	(*k)++;
}
