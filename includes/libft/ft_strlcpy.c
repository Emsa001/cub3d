/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:59:09 by triedel           #+#    #+#             */
/*   Updated: 2023/11/17 11:37:15 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	i = 0;
	while (dstsize > 1 && src[i] != '\0')
	{
		*dst++ = src[i++];
		dstsize--;
	}
	if (dstsize > 0)
		*dst = '\0';
	while (src[i])
		i++;
	return (i);
}
