/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:57:41 by escura            #+#    #+#             */
/*   Updated: 2024/05/21 14:21:57 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_addchar(char **str, char c)
{
	int		len;
	char	*new_str;

	len = ft_strlen(*str);
	new_str = (char *)ft_malloc((len + 2) * sizeof(char));
	ft_strncpy(new_str, *str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	ft_free(*str);
	*str = new_str;
}
