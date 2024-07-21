/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:36:20 by triedel           #+#    #+#             */
/*   Updated: 2023/11/17 21:16:48 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int				dir;
	unsigned int	i;

	if (!src && !dst && len > 0)
		return (NULL);
	if (src < dst)
	{
		dir = -1;
		i = len - 1;
	}
	else
	{
		dir = 1;
		i = 0;
	}
	while (i < len)
	{
		((char *) dst)[i] = ((char *) src)[i];
		i += dir;
	}
	return (dst);
}
