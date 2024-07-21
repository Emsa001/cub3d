/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:30:33 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 15:36:31 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool is_touching(float px, float py)
{
	const int		x = px / BLOCK_SIZE;
	const int		y = py / BLOCK_SIZE;
	const t_cube	*c = cube();

	if (x < 0 || y < 0 || x >= c->map->width || y >= c->map->height)
		return (true);
	if (c->map->map[y][x] == WALL)
		return (true);
    return (false);
}


