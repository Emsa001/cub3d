/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:34:58 by triedel           #+#    #+#             */
/*   Updated: 2023/11/17 23:07:01 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*cand;

	cand = NULL;
	while (1)
	{
		if (*s == (char) c)
			cand = (char *) s;
		if (*s == '\0')
			break ;
		s++;
	}
	return (cand);
}
