/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:57:41 by escura            #+#    #+#             */
/*   Updated: 2024/05/03 20:45:41 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_char(char *str, char c)
{
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = ft_malloc((len + 2) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strncpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	ft_free(str);
	return (new_str);
}
