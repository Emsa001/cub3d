/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:51 by btvildia          #+#    #+#             */
/*   Updated: 2024/07/18 17:23:51 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_zero_count(char **map)
{
	int	i;
	int	j;
	int	zero;

	i = 0;
	j = 0;
	zero = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0')
				zero++;
			j++;
		}
		i++;
	}
	return (zero);
}

void	check_valid(char **map, t_map *map_info)
{
	t_point	size;
	t_point	*begin_points;
	char	to_fill[7];

	begin_points = ft_malloc(sizeof(t_point) * (get_zero_count(map) + 1));
	begin_points = get_begin_points(map, begin_points);
	begin_points[get_zero_count(map)].x = -1;
	begin_points[get_zero_count(map)].y = -1;
	to_fill[0] = '0';
	to_fill[1] = 'N';
	to_fill[2] = 'S';
	to_fill[3] = 'W';
	to_fill[4] = 'E';
	to_fill[5] = 'D';
	to_fill[6] = '2';
	size.x = map_info->width + 1;
	size.y = map_info->height;
	fill_loop(to_fill, begin_points, map_info, size);
	ft_free(begin_points);
}

t_map	*check_map(char **map, int size)
{
	t_map	*map_info;

	map_info = ft_malloc(sizeof(t_map));
	map_info->width = 0;
	map_info->height = 0;
	map_info->no = NULL;
	map_info->so = NULL;
	map_info->we = NULL;
	map_info->ea = NULL;
	map_info->map = NULL;
	get_no_so_we_ea(map_info, map);
	map_info->f = get_color(map_info, map, 'F');
	map_info->c = get_color(map_info, map, 'C');
	get_2d_map(map_info, map, size);
	get_map_sizes(map_info, map_info->map);
	check_valid(map_info->map, map_info);
	map_info->doors = init_block(map_info, 'D');
	map_info->blocks = init_block(map_info, '2');
	return (map_info);
}
