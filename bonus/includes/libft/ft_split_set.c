/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:07:40 by escura            #+#    #+#             */
/*   Updated: 2024/05/31 01:15:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static int	count_splits(char *str, char *set)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (ft_isinset(*str, set))
		{
			if (in_word)
			{
				in_word = 0;
				count++;
			}
		}
		else
			in_word = 1;
		str++;
	}
	if (in_word)
		count++;
	return (count);
}

static char	**ft_split_add(char **result, int i, char *start, char *end)
{
	int	len;

	if (start != end)
	{
		len = end - start;
		result[i] = ft_malloc((len + 1) * sizeof(char));
		ft_strncpy(result[i], start, len);
		result[i][len] = '\0';
		i++;
	}
	return (result);
}

char	**ft_splitset(char *str, char *set)
{
	char	**result;
	int		i;
	char	*start;
	char	*end;

	if (!str || !set)
		return (NULL);
	result = ft_malloc((count_splits(str, set) + 1) * sizeof(char *));
	i = 0;
	start = str;
	end = str;
	while (*end)
	{
		if (ft_isinset(*end, set))
		{
			if (start != end)
				result = ft_split_add(result, i++, start, end);
			start = end + 1;
		}
		end++;
	}
	if (start != end)
		result = ft_split_add(result, i++, start, end);
	result[i] = NULL;
	return (result);
}
