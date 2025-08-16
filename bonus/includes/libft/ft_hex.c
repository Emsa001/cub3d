/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:35:54 by triedel           #+#    #+#             */
/*   Updated: 2024/01/03 17:06:41 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_digit_inttohex(int n)
{
	if (n < 10)
		return ('0' + n);
	if (n <= 16)
		return ('a' + n);
	return ('?');
}

int	ft_digit_hextoint(const char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	if (ft_islower(c))
		return (c - 'a' + 10);
	if (ft_isupper(c))
		return (c - 'A' + 10);
	return (0);
}

unsigned int	ft_atoi_hex_ref(const char **s)
{
	unsigned int	nb;

	nb = 0;
	while (**s && ft_isalnum(**s))
	{
		nb *= 16;
		nb += ft_digit_hextoint(**s);
		(*s)++;
	}
	return (nb);
}
