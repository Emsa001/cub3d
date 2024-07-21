/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:51:01 by triedel           #+#    #+#             */
/*   Updated: 2024/01/05 15:31:44 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstget(t_list *lst, int index)
{
	int		i;

	if (!lst)
		return (NULL);
	i = 0;
	while (lst->next && i < index)
	{
		lst = lst->next;
		i++;
	}
	if (i == index)
		return (lst);
	return (NULL);
}
