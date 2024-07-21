/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:35:16 by triedel           #+#    #+#             */
/*   Updated: 2023/11/17 22:01:06 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cur;

	cur = (unsigned char *) s;
	while (n-- > 0)
	{
		if (*cur == (unsigned char) c)
			return (cur);
		cur++;
	}
	return (NULL);
}
