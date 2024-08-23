/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:34:15 by triedel           #+#    #+#             */
/*   Updated: 2023/11/17 10:57:56 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = 0;
	while (*dst != '\0' && len < size)
	{
		len++;
		dst++;
	}
	while (*src != '\0' && len + 1 < size)
	{
		*(dst++) = *(src++);
		len++;
	}
	if (len < size)
		*dst = '\0';
	while (*src++ != '\0')
		len++;
	return (len);
}
