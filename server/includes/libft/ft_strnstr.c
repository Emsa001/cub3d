/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:30:49 by triedel           #+#    #+#             */
/*   Updated: 2023/11/17 23:06:43 by triedel          ###   ########.fr       */
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
