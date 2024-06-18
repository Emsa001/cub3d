/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:28:09 by triedel           #+#    #+#             */
/*   Updated: 2024/06/18 20:30:22 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	strlen;

	strlen = ft_strlen(s);
	if (start > ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	if (strlen - start < len)
		len = strlen - start;
	substr = ft_malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

char	*ft_remove_substr(char *str, char *sub)
{
	char	*result;
	char	*found;
	int		len;
	int		new_len;
	int		i;

	result = NULL;
	found = ft_strstr(str, sub);
	if (!str || !sub)
		return (NULL);
	if (found)
	{
		len = ft_strlen(sub);
		new_len = ft_strlen(str) - len;
		result = ft_malloc((new_len + 1) * sizeof(char));
		if (result)
		{
			i = found - str;
			ft_strncpy(result, str, i);
			ft_strncpy(result + i, found + len, new_len - i);
			result[new_len] = '\0';
		}
	}
	return (result);
}
