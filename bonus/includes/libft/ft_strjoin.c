/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:06:20 by triedel           #+#    #+#             */
/*   Updated: 2024/10/02 18:16:58 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len1;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	size = len1 + ft_strlen(s2) + 1;
	str = ft_malloc((size) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, size);
	ft_strlcpy(str + len1, s2, size);
	return (str);
}

char	*ft_strappend(char const *s1, char const *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (ft_free((void *)s1), NULL);
	res = ft_strjoin(s1, s2);
	ft_free((void *)s1);
	return (res);
}

char	*ft_strjoin_itoa(char const *s1, int n)
{
	char	*str;
	char	*itoa;

	itoa = ft_itoa(n);
	str = ft_strjoin(s1, itoa);
	ft_free(itoa);
	return (str);
}
