/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isonly.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:01:04 by escura            #+#    #+#             */
/*   Updated: 2024/05/21 14:01:51 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isonly(char *str, char c)
{
	while (*str)
	{
		if (*str != c)
			return (false);
		str++;
	}
	return (true);
}
