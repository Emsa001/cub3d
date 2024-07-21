/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:04:33 by triedel           #+#    #+#             */
/*   Updated: 2023/11/13 11:12:21 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	str = ft_strdup(s);
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		str[i] = (*f)(i, str[i]);
		i++;
	}
	return (str);
}
