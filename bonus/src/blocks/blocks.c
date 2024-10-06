/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:06:12 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/06 16:37:15 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	side_check(t_block *blocks, int k, t_float point, char **map)
{
	if (get_side(point.x, point.y, map) == 1 || get_side(point.x, point.y,
			map) == 3)
		blocks[k - 1].add_y = 30;
	else if (get_side(point.x, point.y, map) == 2 || get_side(point.x, point.y,
			map) == 4)
		blocks[k - 1].add_x = 30;
}

t_block	*init_door(t_map *map_info)
{
	t_block	*blocks;
	t_float	point;
	int		k;

	point.y = 0;
	point.x = 0;
	map_info->blocks = NULL;
	blocks = ft_malloc(sizeof(t_block) * (count_c(map_info->map, 'D') + 1));
	k = 0;
	while (map_info->map[(int)point.y] != NULL)
	{
		point.x = 0;
		while (map_info->map[(int)point.y][(int)point.x] != '\0')
		{
			if (map_info->map[(int)point.y][(int)point.x] == 'D')
			{
				init_once(blocks, point, &k, 'D');
				side_check(blocks, k, point, map_info->map);
			}
			point.x++;
		}
		point.y++;
	}
	terminate_blocks(&blocks, k);
	return (blocks);
}

void	add_block(float angle)
{
	int		i;
	t_block	*new_blocks;
	t_block	*blocks;
	t_float	point;

	point.x = player()->x - 0.5 + 2.5 * cos(angle);
	point.y = player()->y - 0.5 + 2.5 * sin(angle);
	blocks = cube()->map->blocks;
	i = 0;
	while (blocks[i].x != -1)
	{
		i++;
		if (i == MAX_BLOCK)
			return ;
	}
	new_blocks = ft_malloc(sizeof(t_block) * (i + 2));
	i = 0;
	while (blocks[i].x != -1)
	{
		new_blocks[i] = blocks[i];
		i++;
	}
	init_once(new_blocks, point, &i, '2');
	terminate_blocks(&new_blocks, i);
	cube()->map->blocks = new_blocks;
}

void	remove_block(float angle)
{
	t_cube	*c;
	int		id;
	t_block	*new_blocks;
	int		i;
	int		j;

	i = 0;
	j = 0;
	c = cube();
	id = get_block_id(c->map->blocks, player()->x, player()->y, angle);
	if (id == -1)
		return ;
	new_blocks = ft_malloc(sizeof(t_block) * (MAX_BLOCK + 1));
	while (c->map->blocks[i].x != -1)
	{
		if (i != id)
			new_blocks[j++] = c->map->blocks[i];
		i++;
	}
	terminate_blocks(&new_blocks, j);
	c->map->blocks = new_blocks;
}
