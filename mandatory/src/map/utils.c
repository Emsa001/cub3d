/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:59:54 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/23 13:50:37 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	split_and_parse_line(char *line, char *str)
{
	int		i;
	int		j;
	char	**check_split;

	i = 0;
	j = 0;
	if (!line || !str)
		return (-1);
	check_split = ft_split(line, ' ');
	if (ft_arrlen(check_split) != 2)
	{
		ft_arrdel((void **)check_split);
		ft_error("Invalid map info");
	}
	ft_arrdel((void **)check_split);
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	while (line[i] == str[j] && line[i] != '\0' && str[j] != '\0')
	{
		i++;
		j++;
	}
	while (line[i] != '\0' && ft_isspace(line[i]) && line[i] != '\n')
		i++;
	return (i);
}

char	*get_next_string(char *line, char *str)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = split_and_parse_line(line, str);
	if (i == -1)
		return (NULL);
	tmp = ft_malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	while (line[i] != '\0' && line[i] != '\n')
	{
		tmp[j] = line[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
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
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E' && ft_isspace(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
