/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:35:07 by triedel           #+#    #+#             */
/*   Updated: 2023/11/17 23:06:31 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	diff;

	while (n-- > 0)
	{
		diff = (unsigned char) *s1 - (unsigned char) *s2;
		if (diff)
			return (diff);
		if (*s1 == '\0' || *s2 == '\0')
			break ;
		s1++;
		s2++;
	}
	return (0);
}
