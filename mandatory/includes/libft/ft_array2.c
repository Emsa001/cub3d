/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:28:07 by escura            #+#    #+#             */
/*   Updated: 2024/05/22 17:24:47 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// free NULL-terminated array
void	ft_arrdel(void **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			ft_free(arr[i++]);
		ft_free(arr);
	}
}

// free a NULL-terminated array of NULL-terminated arrays
void	ft_arrarrdel(void ***arr)
{
	int	i;

	i = 0;
	while (arr[i])
		ft_arrdel(arr[i++]);
	ft_free(arr);
}

void	ft_arrsdel(char ***arr)
{
	int	i;

	i = 0;
	while (arr[i])
		ft_arrdel((void **)arr[i++]);
}
