/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:30:49 by triedel           #+#    #+#             */
/*   Updated: 2024/05/21 14:19:36 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	cand;
	int				i;
	char			*ndl;

	if (*needle == '\0')
		return ((char *) haystack);
	cand = 0;
	while (haystack[cand] && cand < len)
	{
		i = 0;
		ndl = (char *) needle;
		while (cand + i < len && haystack[cand + i] && \
				*needle && haystack[cand + i] == *ndl)
		{
			i++;
			ndl++;
		}
		if (*ndl == '\0')
			return ((char *) haystack + cand);
		cand++;
	}
	return (NULL);
}
