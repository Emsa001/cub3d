/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:23:46 by escura            #+#    #+#             */
/*   Updated: 2024/03/09 19:24:35 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delims)
{
	static char	*s = NULL;
	char		*start;

	if ((!s && !str) || !delims)
		return (NULL);
	if (str)
		s = str;
	while (*s != '\0' && ft_charinset(*s, delims))
		s++;
	start = s;
	while (*s != '\0' && !ft_charinset(*s, delims))
		s++;
	if (*start == '\0')
		return (NULL);
	*s++ = '\0';
	return (start);
}