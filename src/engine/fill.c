/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:52:35 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/18 15:10:30 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	neighbor_check(char **tab, t_point size, t_point begin, char to_fill[])
{
	int		i;
	char	neighbor;
	t_point	d[4];

	d[0] = (t_point){begin.x - 1, begin.y};
	d[1] = (t_point){begin.x + 1, begin.y};
	d[2] = (t_point){begin.x, begin.y - 1};
	d[3] = (t_point){begin.x, begin.y + 1};
	i = 0;
	neighbor = 0;
	while (i < 4)
	{
		if (d[i].y >= 0 && d[i].y < size.y && d[i].x >= 0 && d[i].x < size.x)
		{
			neighbor = tab[d[i].y][d[i].x];
			if ((neighbor != '1' && neighbor != 'X' && neighbor != 'N'
					&& neighbor != '0') || (neighbor == '0' && d[i].x == 0))
				ft_error("Map is not closed");
		}
		i++;
	}
}

void	fill(char **tab, t_point size, t_point begin, char to_fill[])
{
	char	c;
	int		i;

	if (begin.y < 0 || begin.y >= size.y || begin.x < 0 || begin.x >= size.x)
		return ;
	c = tab[begin.y][begin.x];
	i = 0;
	while (i < 2)
	{
		if (c == to_fill[i])
		{
			neighbor_check(tab, size, begin, to_fill);
			tab[begin.y][begin.x] = 'X';
			print_map(tab);
			fill(tab, size, (t_point){begin.x - 1, begin.y}, to_fill);
			print_map(tab);
			fill(tab, size, (t_point){begin.x + 1, begin.y}, to_fill);
			print_map(tab);
			fill(tab, size, (t_point){begin.x, begin.y - 1}, to_fill);
			print_map(tab);
			fill(tab, size, (t_point){begin.x, begin.y + 1}, to_fill);
			break ;
		}
		i++;
	}
}

t_point	*get_begin_points(char **map)
{
	t_point	*begin_points;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0')
				k++;
			j++;
		}
		i++;
	}
	begin_points = ft_malloc(sizeof(t_point) * (k + 1));
	i = 0;
	k = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0')
			{
				begin_points[k].x = j;
				begin_points[k].y = i;
				k++;
			}
			j++;
		}
		i++;
	}
	begin_points[k].x = -1;
	begin_points[k].y = -1;
	return (begin_points);
}

void	check_valid(char **map, t_map *map_info)
{
	t_point	size;
	int		i;
	t_point	*begin_points;
	char	to_fill[2];
	char	**map2;

	begin_points = get_begin_points(map);
	to_fill[0] = 'N';
	to_fill[1] = '0';
	size.x = map_info->width + 1;
	size.y = map_info->height;
	i = 0;
	map2 = ft_malloc(sizeof(char *) * (map_info->height + 1));
	while (i < map_info->height)
	{
		map2[i] = ft_strdup(map[i]);
		i++;
	}
	map2[i] = NULL;
	i = 0;
	while (begin_points[i].x != -1)
	{
		fill(map2, size, begin_points[i], to_fill);
		i++;
	}
	ft_free(begin_points);
	ft_arrdel((void **)map2);
	exit(0);
}
