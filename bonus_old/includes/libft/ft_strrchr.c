/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:34:58 by triedel           #+#    #+#             */
/*   Updated: 2024/05/21 14:19:58 by escura           ###   ########.fr       */
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
