/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:59:54 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/23 17:21:00 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (line[i] != '1' && line[i] != 'D' && line[i] != 'G' && line[i] != 'P'
			&& line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E' && line[i] != 'M'
			&& ft_isspace(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
