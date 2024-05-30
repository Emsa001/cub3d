/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:35:26 by triedel           #+#    #+#             */
/*   Updated: 2023/11/17 11:09:47 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	diff;

	while (n-- > 0)
	{
		diff = *((unsigned char *) s1) - *((unsigned char *) s2);
		if (diff)
			return (diff);
		s1++;
		s2++;
	}
	return (0);
}
