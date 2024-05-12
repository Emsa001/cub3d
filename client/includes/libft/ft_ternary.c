/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ternary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:40:06 by triedel           #+#    #+#             */
/*   Updated: 2024/01/12 22:41:18 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

int	ft_ternary_int(bool cond, int a, int b)
{
	if (cond)
		return (a);
	else
		return (b);
}

float	ft_ternary_float(bool cond, float a, float b)
{
	if (cond)
		return (a);
	else
		return (b);
}
