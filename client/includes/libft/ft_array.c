/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:14:30 by triedel           #+#    #+#             */
/*   Updated: 2024/05/12 14:47:38 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// free NULL-terminated array
void	ft_arrdel(void **arr)
{
	int	i;

	i = 0;
	if(arr){
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

// applies function f to all elements of NULL-terminated array arr
void	ft_arriter(void **arr, void (*f)(void **))
{
	while (*arr)
		f(*arr++);
}

int	ft_strarr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

// void	ft_arrarrprint(void ***arr)
// {
// 	ft_arriter((void **) arr, ft_arrprint);
// }
