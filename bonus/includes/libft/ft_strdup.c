/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:11:34 by triedel           #+#    #+#             */
/*   Updated: 2024/05/21 14:21:31 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*dup;
	int		size;

	size = ft_strlen(src) + 1;
	dup = ft_malloc(size * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, src, size);
	return (dup);
}
