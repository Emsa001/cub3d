/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:14:30 by triedel           #+#    #+#             */
/*   Updated: 2024/05/22 18:34:03 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_arrjoin(char **arr, char *s)
{
	char	*str;
	int		i;
	char	*temp;

	str = "";
	i = 0;
	while (arr[i])
	{
		temp = "";
		if (i > 0)
			temp = ft_strjoin(str, s);
		str = ft_strjoin(temp, arr[i]);
		i++;
	}
	return (str);
}

// applies function f to all elements of NULL-terminated array arr
void	ft_arriter(void **arr, void (*f)(void **))
{
	while (*arr)
		f(*arr++);
}

void	ft_strarr_print(char **arr)
{
	int	i;

	ft_putendl_fd("--- array: ---\n", 1);
	i = 0;
	while (arr[i])
	{
		ft_putendl_fd(arr[i], 1);
		i++;
	}
	ft_putendl_fd("---\n", 1);
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
