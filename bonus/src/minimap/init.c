/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:13:57 by escura            #+#    #+#             */
/*   Updated: 2024/08/23 14:50:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap_init(void)
{
	t_minimap	*minimap;

	minimap = ft_malloc(sizeof(t_minimap));
	minimap->size = 1.8;
	minimap->x = WIDTH - MINIMAP_PIXEL_WIDTH;
	minimap->y = 0;
	minimap->radius = MINIMAP_RADIUS / minimap->size;
	cube()->map->minimap = minimap;
}

t_minimap	*minimap(void)
{
	return (cube()->map->minimap);
}