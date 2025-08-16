/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:52:35 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/05 19:55:02 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%s", map[i]);
		i++;
	}
	printf("\n");
	printf("\n");
	usleep(50000);
}

void	neighbor_check(char **tab, t_point size, t_point begin)
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
			if ((neighbor != '1' && neighbor != 'D' && neighbor != 'X'
					&& neighbor != 'N' && neighbor != '0' && neighbor != 'S'
					&& neighbor != 'W' && neighbor != 'E' && neighbor != 'G'
					&& neighbor != 'P' && neighbor != 'M'))
				ft_error("Map error");
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
	while (i < 9)
	{
		if (c == to_fill[i])
		{
			if (begin.y >= size.y - 1 || begin.x >= size.x - 1)
				ft_error("Map is not closed");
			neighbor_check(tab, size, begin);
			tab[begin.y][begin.x] = 'X';
			fill(tab, size, (t_point){begin.x - 1, begin.y}, to_fill);
			fill(tab, size, (t_point){begin.x + 1, begin.y}, to_fill);
			fill(tab, size, (t_point){begin.x, begin.y - 1}, to_fill);
			fill(tab, size, (t_point){begin.x, begin.y + 1}, to_fill);
			break ;
		}
		i++;
	}
}

t_point	*get_begin_points(char **map, t_point *begin_points)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
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
	return (begin_points);
}

void	fill_loop(char to_fill[], t_point *begin_points, t_map *map_info,
		t_point size)
{
	int		i;
	char	**map2;

	i = 0;
	map2 = ft_malloc(sizeof(char *) * (map_info->height + 1));
	while (i < map_info->height)
	{
		map2[i] = ft_strdup(map_info->map[i]);
		i++;
	}
	map2[i] = NULL;
	i = 0;
	while (begin_points[i].x != -1)
	{
		fill(map2, size, begin_points[i], to_fill);
		i++;
	}
	ft_arrdel((void **)map2);
}
