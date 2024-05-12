/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:28:07 by escura            #+#    #+#             */
/*   Updated: 2024/04/19 17:59:33 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
