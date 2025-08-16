/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 08:50:45 by triedel           #+#    #+#             */
/*   Updated: 2024/05/31 01:41:56 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcount(const char *s, const char *set)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (ft_charinset(*s, set))
			count++;
		s++;
	}
	return (count);
}

char	*ft_strstrip(const char *s, const char *set)
{
	char	*res;
	char	*res_orig;

	if (!s)
		return (NULL);
	res = ft_malloc((ft_strlen(s) - ft_strcount(s, set) + 1) * sizeof(char));
	res_orig = res;
	while (*s)
	{
		if (!ft_charinset(*s, set))
			*res++ = *s;
		s++;
	}
	*res = '\0';
	return (res_orig);
}

void	ft_strstrip_char(const char *s, const char c)
{
	char	*res;

	res = ft_strchr(s, c);
	if (res)
		*res = '\0';
}
