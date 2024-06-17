/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:36:10 by triedel           #+#    #+#             */
/*   Updated: 2024/06/17 14:13:56 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charinset(int c, const char *set)
{
	char	*s;

	s = (char *)set;
	while (*s != '\0')
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	ft_isspace(int c)
{
	return (ft_charinset(c, "\t\n\v\f\r "));
}

int	ft_atoi(const char *str)
{
	char	*s;
	long	nb;
	int		sign;

	s = (char *)str;
	sign = 1;
	nb = 0;
	while (ft_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && ft_isdigit(*s))
	{
		nb *= 10;
		nb += *s - '0';
		s++;
	}
	return (sign * nb);
}

// note: does not skip spaces
int	ft_atoi_ref(const char **s)
{
	long	nb;
	int		sign;

	sign = 1;
	nb = 0;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	while (**s && ft_isdigit(**s))
	{
		nb *= 10;
		nb += **s - '0';
		(*s)++;
	}
	return (sign * nb);
}
