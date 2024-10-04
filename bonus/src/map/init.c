/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:19:15 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 14:58:05 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_block	*init_generators(t_map *map_info, char **map)
{
	t_block	*generators;
	int		i;
	int		j;
	int		k;
	t_point	*points;

	points = ft_malloc(sizeof(t_point) * (count_c(map, 'G') + 1));
	get_points(&points, map, 'G');
	i = 0;
	j = 0;
	k = 0;
	map_info->generators = NULL;
	generators = ft_malloc(sizeof(t_block) * (count_c(map, 'G') + 1));
	while (points[i].x != -1)
	{
		generators[k].x = points[i].x;
		generators[k].y = points[i].y;
		k++;
		i++;
	}
	generators[k].x = -1;
	generators[k].y = -1;
	return (generators);
}

t_block	*init_map_block(t_map *map_info)
{
	t_block	*blocks;
	int		k;

	map_info->blocks = NULL;
	blocks = ft_calloc(sizeof(t_block), MAX_BLOCK + 1);
	k = 0;
	blocks[k].x = -1;
	blocks[k].y = -1;
	blocks[k].id = -1;
	blocks[k].s_x = -1;
	blocks[k].s_y = -1;
	blocks[k].type = '\0';
	return (blocks);
}

t_map	*check_map(char **map, int size)
{
	t_map	*map_info;

	map_info = ft_malloc(sizeof(t_map));
	map_info->width = 0;
	map_info->height = 0;
	map_info->portal = false;
	map_info->map = NULL;
	map_info->lines = NULL;
	map_info->sprites = NULL;
	map_info->facing = NULL;
	get_2d_map(map_info, map, size);
	get_map_sizes(map_info, map_info->map);
	check_valid(map_info->map, map_info);
	map_info->doors = init_door(map_info);
	map_info->lines = init_map_block(map_info);
	map_info->blocks = init_map_block(map_info);
	map_info->generators = init_generators(map_info, map);
	map_info->facing = init_map_facing(map);
	map_info->sprites = init_map_sprites(map_info, map);
	map_info->sprite_count = (SPRITE_THICKNESS * (count_c(map, 'P')
				+ count_c(map, 'M'))) * 64;
	map_info->portals = ft_malloc(sizeof(t_block) * (count_c(map, 'P') + 1));
	get_points(&map_info->portals, map, 'P');
	map_info->editor_mode = false;
	return (map_info);
}

void	map_init(char *av)
{
	char	**map;
	int		i;
	int		fd;
	char	*c;
	t_map	*map_info;

	c = ft_strjoin("./maps/", av);
	fd = open(c, O_RDONLY);
	ft_free(c);
	if (fd == -1)
		ft_error("Map not found");
	map = ft_malloc(sizeof(char *) * MAX_SIZE);
	i = 0;
	while (1)
	{
		if (i >= MAX_SIZE)
			ft_error("Map too big");
		map[i] = get_next_line(fd);
		if (!map[i])
			break ;
		i++;
	}
	map[i] = NULL;
	close(fd);
	map_info = check_map(map, i);
	ft_arrdel((void **)map);
	cube()->map = map_info;
}

t_map	*get_map(void)
{
	return (cube()->map);
}
