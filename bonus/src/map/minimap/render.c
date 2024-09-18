/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:16:56 by escura            #+#    #+#             */
/*   Updated: 2024/09/18 16:55:27 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_minimap_utils	*set_utils(void)
{
	t_minimap_utils	*utils;

	utils = ft_malloc(sizeof(t_minimap_utils));
	utils->center_x = minimap()->x + MINIMAP_PIXEL_WIDTH / 2.0f;
	utils->center_y = minimap()->y + MINIMAP_PIXEL_HEIGHT / 2.0f;
	utils->start_x = player()->x - MINIMAP_RADIUS / (float)MINIMAP_BLOCK_SIZE;
	utils->start_y = player()->y - MINIMAP_RADIUS / (float)MINIMAP_BLOCK_SIZE;
	utils->end_x = utils->start_x + MINIMAP_RADIUS * 2
		/ (float)MINIMAP_BLOCK_SIZE;
	utils->end_y = utils->start_y + MINIMAP_RADIUS * 2
		/ (float)MINIMAP_BLOCK_SIZE;
	return (utils);
}

static void	set_block(int i, int j, t_minimap_utils *utils)
{
	const t_cube	*c = cube();
	const t_minimap	*m = minimap();
	int				screen_x;
	int				screen_y;

	if (c->map && i >= 0 && i < c->map->height && j >= 0 && j < c->map->width && c->map->map[i])
	{
		// printf("%c\n", c->map->map[i][j]);
		if (c->map->map[i][j] == '1')
		{
			screen_x = m->x + (int)((j - utils->start_x) * MINIMAP_BLOCK_SIZE);
			screen_y = m->y + (int)((i - utils->start_y) * MINIMAP_BLOCK_SIZE);
			screen_x -= MINIMAP_BLOCK_SIZE * 2.05;
			screen_y -= MINIMAP_BLOCK_SIZE * 2.05;
			minimap_block(j, i, screen_x, screen_y);
		}
	}
}

void	render_minimap(void)
{
	t_minimap_utils *utils;
	int i;
	int j;

	utils = set_utils();
	i = (int)utils->start_y;
	draw_circle(utils->center_x, utils->center_y, minimap()->radius,
		MINIMAP_COLOR);
	while (i < (int)utils->end_y)
	{
		j = (int)utils->start_x;
		while (j < (int)utils->end_x)
		{
			set_block(i, j, utils);
			j++;
		}
		i++;
	}

	ft_free(utils);
	minimap_draw_player();
}