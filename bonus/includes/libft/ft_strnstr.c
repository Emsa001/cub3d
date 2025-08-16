/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:30:49 by triedel           #+#    #+#             */
/*   Updated: 2024/10/02 18:17:22 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	cand;
	int				i;
	char			*ndl;

	if (*needle == '\0')
		return ((char *)haystack);
	cand = 0;
	while (haystack[cand] && cand < len)
	{
		i = 0;
		ndl = (char *)needle;
		while (cand + i < len && haystack[cand + i] && *needle && haystack[cand
				+ i] == *ndl)
		{
			i++;
			ndl++;
		}
		if (*ndl == '\0')
			return ((char *)haystack + cand);
		cand++;
	}
	return (NULL);
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
