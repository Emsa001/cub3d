/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:22:38 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/27 18:56:03 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_2d_map(t_map *map_info, char **map, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map_info->map = ft_malloc(sizeof(char *) * (size + 1));
	while (map[i] != NULL)
	{
		if (ft_check_line(map[i]) == 0)
		{
			if (j > 0)
				ft_error("Map should be at the end");
			i++;
		}
		else
		{
			map_info->map[j] = ft_strdup(map[i]);
			j++;
			i++;
		}
	}
	if (j == 0)
		ft_error("No map found");
	map_info->map[j] = NULL;
}

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
	map_info->width -= 1;
	map_info->height = i;
}

int	ft_check_correct(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E' && ft_isspace(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
