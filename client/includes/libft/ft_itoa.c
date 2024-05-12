/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:06:10 by triedel           #+#    #+#             */
/*   Updated: 2024/05/04 10:17:06 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*s;
	long	nb;
	int		intlen;
	int		i;

	nb = n;
	intlen = ft_intlen(nb);
	s = ft_malloc((intlen + 1) * sizeof(char));
	if (!s)
		return (NULL);
	if (nb < 0)
	{
		s[0] = '-';
		nb = -nb;
	}
	s[intlen] = '\0';
	i = intlen - 1;
	while (1)
	{
		s[i--] = '0' + nb % 10;
		nb /= 10;
		if (nb <= 0)
			break ;
	}
	return (s);
}

char	*ft_itoa_sign(int n, bool with_sign)
{
	char	*numstr;
	char	*res;

	if (with_sign && n > 0)
	{
		numstr = ft_itoa(n);
		res = ft_strjoin("+", numstr);
		if (!res && numstr)
			free(numstr);
		return (res);
	}
	return (ft_itoa(n));
}
