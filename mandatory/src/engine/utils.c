/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:30:33 by escura            #+#    #+#             */
/*   Updated: 2024/08/06 17:49:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool is_touching(float px, float py)
{
	const int		x = px / BLOCK_SIZE;
	const int		y = py / BLOCK_SIZE;
	const t_cube	*c = cube();

	if (x < 0 || y < 0 || x >= c->map->width || y >= c->map->height)
		return (true);
	else if (c->map->map[y][x] == WALL)
		return (true);		
    return (false);
}


