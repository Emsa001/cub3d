/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:59:54 by triedel           #+#    #+#             */
/*   Updated: 2024/01/12 13:59:58 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_min(int a, int b)
{
	return (ft_min_int(a, b));
}

int	ft_min_int(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

float	ft_min_float(float a, float b)
{
	if (a > b)
		return (b);
	else
		return (a);
}
