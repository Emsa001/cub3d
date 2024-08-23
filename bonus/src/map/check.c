/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:51 by btvildia          #+#    #+#             */
/*   Updated: 2024/08/23 19:05:43 by marvin           ###   ########.fr       */
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
	char	to_fill[6];

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
	size.x = map_info->width + 1;
	size.y = map_info->height;
	fill_loop(to_fill, begin_points, map_info, size);
	ft_free(begin_points);
}

int count_lines(char **map)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	
	while (map[i] != NULL)
	{
		if (ft_strncmp(map[i], "Line", 4) == 0)
			count++;
		i++;
	}
	return (count);
}

float ft_float_atoi(char *str)
{
	float res;
	float dec;
	int i;
	int j;
	int sign;
	
	i = 0;
	j = 0;
	sign = 1;
	res = 0;
	dec = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != '.' && str[i] != '\0' && str[i] != '\n')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] != '\0' && str[i] != '\n')
		{
			dec = dec * 10 + str[i] - '0';
			i++;
			j++;
		}
	}
	while (j > 0)
	{
		dec = dec / 10;
		j--;
	}
	return (sign * (res + dec));
}


t_block get_line(char *line)
{
	t_block block_line;
	char **line_split;
	
	line_split = ft_split(line, ',');

	int i = 0;
	
	block_line.s_x = ft_float_atoi(line_split[0]);
	block_line.s_y = ft_float_atoi(line_split[1]);
	block_line.x = ft_float_atoi(line_split[2]);
	block_line.y = ft_float_atoi(line_split[3]);
	
	while(line_split[i] != NULL)
	{
		ft_free(line_split[i]);
		i++;
	}
	ft_free(line_split);
	return (block_line);
}

t_block *init_line(t_map *map_info , char **map)
{
	t_block	*lines;
	int		i = 0;
	int		j = 0;
	int		k = 0;
	
	map_info->lines = NULL;
	int line_count = count_lines(map);
	lines = ft_malloc(sizeof(t_block) * (line_count + 1));

	while(map[i] != NULL)
	{
		j = 0;
		while(map[i][j] != '\0')
		{
			if (map[i][j] == 'L' && map[i][j + 1] == 'i' && map[i][j + 2] == 'n' && map[i][j + 3] == 'e' && map[i][j + 4] == ' ')
			{
				lines[k] = get_line(get_next_string(map[i], "Line = "));
				k++;
			}
			j++;
		}
		i++;
	}
	lines[k].x = -1;
	lines[k].y = -1;
	return (lines);
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
	map_info->lines = init_line(map_info, map);
	return (map_info);
}
