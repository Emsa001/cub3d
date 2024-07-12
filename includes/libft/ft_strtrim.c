/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:33:56 by triedel           #+#    #+#             */
/*   Updated: 2023/11/13 11:34:05 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		cur;

	start = 0;
	end = 0;
	while (s1[start] != '\0' && ft_charinset(s1[start], set))
		start++;
	end = start;
	cur = start;
	while (s1[cur] != '\0')
	{
		if (!ft_charinset(s1[cur], set))
			end = cur + 1;
		cur++;
	}
	return (ft_substr(s1, start, end - start));
}
