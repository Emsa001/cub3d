/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:21:26 by btvildia          #+#    #+#             */
/*   Updated: 2024/08/11 16:28:55 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	*get_color(t_map *map_info, char **map, char c)
{
	int		i;
	char	*line;
	char	**tmp;
	int		*colors;

	colors = ft_malloc(sizeof(int) * 3);
	colors[0] = 0;
	colors[1] = 0;
	colors[2] = 0;
	i = 0;
	while (map[i] != NULL)
	{
		line = map[i];
		if (ft_strchr(line, c) != NULL)
		{
			line = get_next_string(line, &c);
			tmp = ft_split(line, ',');
			colors = check_get_color(colors, tmp);
			ft_arrdel((void **)tmp);
			return (colors);
		}
		i++;
	}
	return (colors);
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
		width = ft_strlen(map[i]);
		if (width > map_info->width)
			map_info->width = width;
		i++;
	}
	map_info->width -= 1;
	map_info->height = i - 1; // subtract 1 to avoid accessing beyond the array size
}

void	change_positions(char c, int i, int j)
{
	t_player	*p = player();
	p->x = j + 0.5;
	p->y = i + 0.5;
	p->z = 0;
	if (c == 'N')
		p->angle = 3 * PI / 2;
	else if (c == 'S')
		p->angle = PI / 2;
	else if (c == 'W')
		p->angle = PI;
	else if (c == 'E')
		p->angle = 0;
	
	p->direction = p->angle * (180 / PI);
    while (p->direction >= 360) {
        p->direction -= 360;
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
	map_info->map = ft_malloc(sizeof(char *) * (size));
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
