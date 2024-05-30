/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:55:32 by triedel           #+#    #+#             */
/*   Updated: 2024/01/05 13:55:32 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Parse positive integer, only digits allowed,
// return next char pointer or NULL if no number found
int	ft_parse_uint(const char **s)
{
	int	nb;

	nb = -1;
	while (**s && ft_isdigit(**s))
	{
		if (nb == -1)
			nb = 0;
		nb *= 10;
		nb += **s - '0';
		(*s)++;
	}
	return (nb);
}

// Parse positive integer, only digits allowed,
// return next char pointer or NULL if no number found
const char	*ft_atoi_parse(const char *s, int *num)
{
	long	nb;

	nb = -1;
	while (*s && ft_isdigit(*s))
	{
		if (nb == -1)
			nb = 0;
		nb *= 10;
		nb += *s - '0';
		s++;
	}
	if (nb != -1)
		*num = nb;
	return (s);
}
