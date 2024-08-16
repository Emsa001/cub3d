/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:59:54 by btvildia          #+#    #+#             */
/*   Updated: 2024/08/16 20:20:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map_info(void)
{
	const t_map	*map = cube()->map;
	int			i;

	i = 0;
	printf(GREEN "width: " BLUE "%d\n", map->width);
	printf(GREEN "height: " BLUE "%d\n", map->height);
	printf(GREEN "NO: " BLUE "%s" RESET, map->no);
	printf(GREEN "SO: " BLUE "%s" RESET, map->so);
	printf(GREEN "WE: " BLUE "%s" RESET, map->we);
	printf(GREEN "EA: " BLUE "%s" RESET, map->ea);
	printf(GREEN "\nF: " BLUE " %d, %d, %d\n" RESET, map->f[0], map->f[1],
		map->f[2]);
	printf(GREEN "C: " BLUE " %d, %d, %d\n" RESET, map->c[0], map->c[1],
		map->c[2]);
	printf(GREEN "player_x: " BLUE "%f (%fpx)\n" RESET, player()->x, player()->x_px);
	printf(GREEN "player_y: " BLUE "%f (%fpx)\n" RESET, player()->y, player()->y_px);
	printf(GREEN "player_a: " BLUE "%f\n" RESET, player()->angle);
	printf(GREEN "player_speed: " BLUE "%d\n" RESET, player()->speed);
	printf(GREEN "player_fov: " BLUE "%d\n" RESET, player()->fov);
	while (i < map->height)
	{
		if (ft_strchr(map->map[i], 'N') || ft_strchr(map->map[i], 'S')
			|| ft_strchr(map->map[i], 'W') || ft_strchr(map->map[i], 'E'))
			printf(GREEN "%s" RESET, map->map[i]);
		else
			printf("%s", map->map[i]);
		i++;
	}
	printf("\n");
}

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
	usleep(10000);
}

char	*get_next_string(char *line, char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	**check_split;

	i = 0;
	j = 0;
	tmp = NULL;
	check_split = ft_split(line, ' ');
	if (ft_arrlen(check_split) != 2)
	{
		// ft_arrdel((void **)check_split);
		// ft_error("Invalid map info");
	}
	ft_arrdel((void **)check_split);
	if (!line || !str)
		return (NULL);
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	while (line[i] == str[j] && line[i] != '\0' && str[j] != '\0')
	{
		i++;
		j++;
	}
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	tmp = ft_strdup(line + i);
	return (tmp);
}

int	ft_strlen_space(char *s)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (ft_isspace(s[i]))
			i++;
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

int	ft_check_line(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen_space(line) == 0)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] != '1' && line[i] != 'D' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E' && ft_isspace(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
