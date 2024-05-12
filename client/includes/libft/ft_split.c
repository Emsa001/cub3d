/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:04:50 by triedel           #+#    #+#             */
/*   Updated: 2024/05/03 20:49:38 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// Count number of words delimited by char c
int	ft_countwords(char const *s, char c)
{
	int		count;
	char	last;

	count = 0;
	last = c;
	while (*s != '\0')
	{
		if (*s != c && last == c)
			count++;
		last = *s;
		s++;
	}
	return (count);
}

// Free entire (null-terminated) string array
void	ft_strarr_del(char **strarr)
{
	char	**cur;

	cur = strarr;
	while (*cur)
	{
		free(*cur);
		cur++;
	}
	free(strarr);
}

// Returns a duplicate of the next word, moves s on to the next word
char	*ft_nextword(char **s, char c)
{
	char	last;
	char	*start;

	last = c;
	start = NULL;
	while (**s != '\0')
	{
		if (**s != c && last == c)
			start = *s;
		if (**s == c && last != c)
			return (ft_substr(start, 0, *s - start));
		last = **s;
		(*s)++;
	}
	if (start)
		return (ft_substr(start, 0, *s - start));
	else
		return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**strarr;
	const size_t	size = ft_countwords(s, c);
	unsigned int	i;

	strarr = ft_calloc(size + 1, sizeof(char *));
	if (!strarr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		strarr[i] = ft_nextword((char **)&s, c);
		if (!strarr[i])
		{
			ft_strarr_del(strarr);
			return (NULL);
		}
		i++;
	}
	return (strarr);
}

char	**ft_split_precise(char *str, char c)
{
	int		i;
	int		j;
	int		k;
	char	**arr;

	i = 0;
	j = 0;
	k = 0;
	arr = ft_malloc(sizeof(char *) * (ft_strlen(str) + 1));
	if (!arr)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
		{
			arr[j] = ft_substr(str, k, i - k);
			k = i + 1;
			j++;
		}
		i++;
	}
	arr[j] = ft_substr(str, k, i - k);
	arr[j + 1] = NULL;
	return (arr);
}
