/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:04:50 by triedel           #+#    #+#             */
/*   Updated: 2024/02/01 19:19:29 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// Count number of words delimited by char c
int	ft_countwords_set(char const *s, char *set, char *quotes)
{
	int		count;
	bool	last;
	bool	inquotes;

	count = 0;
	inquotes = false;
	last = true;
	while (*s != '\0')
	{
		if (!ft_charinset(*s, set) && last && !inquotes)
			count++;
		last = ft_charinset(*s, set);
		if (ft_charinset(*s, quotes))
			inquotes = !inquotes;
		s++;
	}
	return (count);
}

// Free entire (null-terminated) string array
// void	ft_strarr_del(char **strarr)
// {
// 	char	**cur;

// 	cur = strarr;
// 	while (*cur)
// 	{
// 		free(*cur);
// 		cur++;
// 	}
// 	free(strarr);
// }

// Returns a duplicate of the next word, moves s on to the next word
char	*ft_nextword_set(char **s, char *set, char *quotes)
{
	bool	last;
	bool	inquotes;
	bool	inset;
	char	*start;

	last = true;
	inquotes = false;
	start = NULL;
	while (**s != '\0')
	{
		inset = ft_charinset(**s, set);
		if (!inset && last && !inquotes)
			start = *s;
		if (inset && !last && inquotes)
			return (ft_substr(start, 0, *s - start));
		last = ft_charinset(**s, set);
		if (ft_charinset(**s, quotes))
			inquotes = !inquotes;
		(*s)++;
	}
	if (start)
		return (ft_substr(start, 0, *s - start));
	else
		return (NULL);
}

char	**ft_split_set(char const *s, char *set, char *quotes)
{
	char			**strarr;
	const size_t	size = ft_countwords_set(s, set, quotes);
	unsigned int	i;

	strarr = ft_calloc(size + 1, sizeof(char *));
	if (!strarr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		strarr[i] = ft_nextword_set((char **) &s, set, quotes);
		if (!strarr[i])
		{
			ft_strarr_del(strarr);
			return (NULL);
		}
		i++;
	}
	return (strarr);
}
