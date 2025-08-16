/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:21:26 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/05 19:55:24 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_sizes(t_map *map_info, char **map)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	j = 0;
	width = 0;
	while (map[i] != NULL)
	{
		width = ft_strlen(map[i]);
		if (width > map_info->width)
			map_info->width = width;
		i++;
	}
	map_info->height = i;
}

void	change_positions(char c, int i, int j)
{
	t_player	*p;

	p = player();
	p->x = j + 0.5;
	p->y = i + 0.5;
	p->z = 0.5;
	if (c == 'N')
		p->angle = 3 * PI / 2;
	else if (c == 'S')
		p->angle = PI / 2;
	else if (c == 'W')
		p->angle = PI;
	else if (c == 'E')
		p->angle = 0;
	p->direction = p->angle * (180 / PI);
	while (p->direction >= 360)
		p->direction -= 360;
}

void	get_player_position(char **map)
{
	int	i;
	int	j;
	int	p_count;

	i = 0;
	j = 0;
	p_count = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				change_positions(map[i][j], i, j);
				p_count++;
			}
			j++;
		}
		i++;
	}
	if (p_count != 1)
		ft_error("Error\nThere must be one player");
}

bool	check_ones(char *str, bool first, bool last)
{
	int	i;

	i = 0;
	if (str[0] != '1' && str[0] != ' ' && str[0] != '\t')
		return (false);
	if (first || last)
	{
		while (str[i] != '\0')
		{
			if (str[i] != '1' && str[i] != ' ' && str[i] != '\t'
				&& str[i] != '\n')
				return (false);
			i++;
		}
	}
	return (true);
}

void	get_2d_map(t_map *map_info, char **map, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map_info->map = ft_malloc(sizeof(char *) * (size + 1));
	while (map[i] != NULL)
	{
		if (i == 0 && !check_ones(map[i], true, false))
			ft_error("Error\nMap must be surrounded by walls");
		if (i == size - 1 && !check_ones(map[i], false, true))
			ft_error("Error\nMap must be surrounded by walls");
		if (!check_ones(map[i], false, false))
			ft_error("Error\nMap must be surrounded by walls");
		map_info->map[j] = ft_strdup(map[i]);
		j++;
		i++;
	}
	if (j == 0)
		ft_error("No map found");
	map_info->map[j] = NULL;
}
