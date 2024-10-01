/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:51 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/01 13:20:19 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_replace(char ***str, char old, char new)
{
	int	i;
	int	j;

	i = 0;
	while ((*str)[i] != NULL)
	{
		j = 0;
		while ((*str)[i][j] != '\0')
		{
			if ((*str)[i][j] == old)
				(*str)[i][j] = new;
			j++;
		}
		i++;
	}
}

void	check_valid(char **map, t_map *map_info)
{
	t_point	size;
	t_point	*begin_points;
	char	to_fill[9];

	ft_replace(&map, ' ', '0');
	begin_points = ft_malloc(sizeof(t_point) * (count_c(map, '0') + 1));
	begin_points = get_begin_points(map, begin_points);
	begin_points[count_c(map, '0')].x = -1;
	begin_points[count_c(map, '0')].y = -1;
	to_fill[0] = '0';
	to_fill[1] = 'N';
	to_fill[2] = 'S';
	to_fill[3] = 'W';
	to_fill[4] = 'E';
	to_fill[5] = 'D';
	to_fill[6] = 'G';
	to_fill[7] = 'P';
	to_fill[8] = 'M';
	size.x = map_info->width + 1;
	size.y = map_info->height;
	fill_loop(to_fill, begin_points, map_info, size);
	ft_free(begin_points);
}

int	count_lines(char **map)
{
	int	i;
	int	count;

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

t_block	get_line(char *line)
{
	t_block	block_line;
	char	**line_split;
	int		i;

	line_split = ft_split(line, ',');
	i = 0;
	block_line.s_x = ft_float_atoi(line_split[0]);
	block_line.s_y = ft_float_atoi(line_split[1]);
	block_line.x = ft_float_atoi(line_split[2]);
	block_line.y = ft_float_atoi(line_split[3]);
	while (line_split[i] != NULL)
	{
		ft_free(line_split[i]);
		i++;
	}
	ft_free(line_split);
	return (block_line);
}

void	get_points(t_point **points, char **map, char c)
{
	int	k;
	int	i;
	int	j;

	k = 0;
	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == c)
			{
				(*points)[k].x = j;
				(*points)[k].y = i;
				k = k + 1;
			}
			j++;
		}
		i++;
	}
	(*points)[k].x = -1;
	(*points)[k].y = -1;
}
