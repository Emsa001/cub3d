/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:59:54 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/17 15:55:22 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map_info(t_map *map)
{
	int	i;

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
	printf(GREEN "player_x: " BLUE "%f\n" RESET, map->player_x);
	printf(GREEN "player_y: " BLUE "%f\n" RESET, map->player_y);
	printf(GREEN "player_a: " BLUE "%f\n" RESET, map->player_a);
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

void	ft_error(char *str)
{
	write(2, "Error: ", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

void	ft_free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
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
}

char	*get_next_string(char *line, char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
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

char	*ft_strstr(char *haystack, char *needle)
{
	size_t	len;

	len = ft_strlen(needle);
	if (!haystack)
		return (NULL);
	if (len == 0 || !*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		if (ft_strncmp(haystack, needle, len) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

char	*ft_remove_substr(char *str, char *sub)
{
	char	*result;
	char	*found;
	int		len;
	int		new_len;
	int		i;

	result = NULL;
	found = ft_strstr(str, sub);
	if (!str || !sub)
		return (NULL);
	if (found)
	{
		len = ft_strlen(sub);
		new_len = ft_strlen(str) - len;
		result = ft_malloc((new_len + 1) * sizeof(char));
		if (result)
		{
			i = found - str;
			ft_strncpy(result, str, i);
			ft_strncpy(result + i, found + len, new_len - i);
			result[new_len] = '\0';
		}
	}
	return (result);
}

int	ft_strlen_space(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (ft_isspace(s[i]) == 1)
			i++;
		if (s[i] != '\0')
			j++;
		i++;
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
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E' && ft_isspace(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
