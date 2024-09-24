/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:21:26 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/23 16:22:20 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	*check_get_color(int *colors, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_arrlen(tmp) != 3)
		ft_error("Invalid color");
	while (tmp[i] != NULL)
	{
		colors[j] = ft_atoi(tmp[i]);
		if (colors[j] < 0 || colors[j] > 255)
			ft_error("Invalid color");
		i++;
		j++;
	}
	return (colors);
}

int	get_color(t_map *map_info, char **map, char *c)
{
	int		i;
	char	*line;
	char	**tmp;
	int		*colors;
	int		color;

	colors = ft_calloc(sizeof(int), 3);
	i = -1;
	while (map[++i] != NULL)
	{
		line = map[i];
		if (ft_strchr(line, c[0]) != NULL)
		{
			line = get_next_string(line, c);
			tmp = ft_split(line, ',');
			ft_free(line);
			colors = check_get_color(colors, tmp);
			color = (colors[0] << 16 | colors[1] << 8 | colors[2]);
			ft_arrdel((void **)tmp);
			ft_free(colors);
			return (color);
		}
	}
	ft_free(colors);
	return (color);
}

void	get_no_so_we_ea(t_map *map_info, char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if (ft_strstr(map[i], "NO ") != NULL)
			map_info->no = get_next_string(map[i], "NO ");
		else if (ft_strstr(map[i], "SO ") != NULL)
			map_info->so = get_next_string(map[i], "SO ");
		else if (ft_strstr(map[i], "WE ") != NULL)
			map_info->we = get_next_string(map[i], "WE ");
		else if (ft_strstr(map[i], "EA ") != NULL)
			map_info->ea = get_next_string(map[i], "EA ");
		i++;
	}
}

void	change_positions(char c, int i, int j)
{
	player()->x = j + 0.5;
	player()->y = i + 0.5;
	if (c == 'N')
		player()->angle = 3 * PI / 2;
	else if (c == 'S')
		player()->angle = PI / 2;
	else if (c == 'W')
		player()->angle = PI;
	else if (c == 'E')
		player()->angle = 0;
	player()->direction = player()->angle * (180 / PI);
	while (player()->direction >= 360)
	{
		player()->direction -= 360;
	}
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
		ft_error("Invalid player position");
}
