/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:13:57 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 20:04:11 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap_init(void)
{
	t_minimap	*minimap;

	minimap = ft_malloc(sizeof(t_minimap));
	minimap->x = WIDTH - WIDTH / 6 - 10;
	minimap->y = HEIGHT - WIDTH / 8 - 10;
	minimap->center_x = minimap->x + WIDTH / 6 / 2;
	minimap->center_y = minimap->y + WIDTH / 8 / 2;
	minimap->last_x = minimap->x + WIDTH / 6;
	minimap->last_y = minimap->y + WIDTH / 8;
	cube()->map->minimap = minimap;
}

void	init_square(t_square *square, float angle)
{
	square->cosangle = cos(angle);
	square->sinangle = sin(angle);
	square->color = 0;
	square->x = 0;
	square->y = 0;
}

t_minimap	*minimap(void)
{
	return (cube()->map->minimap);
}
