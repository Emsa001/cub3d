/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:45:39 by triedel           #+#    #+#             */
/*   Updated: 2024/05/17 13:42:28 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

bool	ft_endswith(const char *s, const char *end)
{
	int	len;
	int	endlen;

	len = ft_strlen(s);
	endlen = ft_strlen(end);
	if (endlen > len)
		return (false);
	return (ft_strcmp(s + len - endlen, end) == 0);
}

bool	ft_startswith(const char *s, const char *start)
{
	int	len;
	int	startlen;

	len = ft_strlen(s);
	startlen = ft_strlen(start);
	if (startlen > len)
		return (false);
	return (ft_strncmp(s, start, startlen) == 0);
}

size_t	ft_strspn(char *s, char *cset)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_charinset(s[i], cset))
		i++;
	return (i);
}
