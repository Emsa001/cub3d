/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:21:26 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/17 18:54:10 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*get_color(t_map *map_info, char **map, char c)
{
	int		i;
	char	*line;
	char	**tmp;
	int		*tmp_color;

	tmp_color = ft_malloc(sizeof(int) * 3);
	tmp_color[0] = -1;
	tmp_color[1] = -1;
	tmp_color[2] = -1;
	i = 0;
	while (map[i] != NULL)
	{
		line = map[i];
		if (ft_strchr(line, c) != NULL)
		{
			line = get_next_string(line, &c);
			tmp = ft_split(line, ',');
			if (ft_arrlen(tmp) != 3)
			{
				ft_free_arr(tmp);
				ft_error("Invalid color");
			}
			tmp_color[0] = ft_atoi(tmp[0]);
			tmp_color[1] = ft_atoi(tmp[1]);
			tmp_color[2] = ft_atoi(tmp[2]);
			ft_free_arr(tmp);
			return (tmp_color);
		}
		i++;
	}
	return (tmp_color);
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
		width = ft_strlen_space(map[i]);
		if (width > map_info->width)
			map_info->width = width;
		i++;
	}
	map_info->height = i;
}

void	get_player_position(t_map *map_info, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				map_info->player_x = j + 0.5;
				map_info->player_y = i + 0.5;
				if (map[i][j] == 'N')
					map_info->player_a = 3 * PI / 2;
				else if (map[i][j] == 'S')
					map_info->player_a = PI / 2;
				else if (map[i][j] == 'W')
					map_info->player_a = PI;
				else if (map[i][j] == 'E')
					map_info->player_a = 0;
				return ;
			}
			j++;
		}
		i++;
	}
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

void	get_2d_map(t_map *map_info, char **map, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map_info->map = ft_malloc(sizeof(char *) * size);
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
