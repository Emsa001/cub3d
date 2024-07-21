/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:07:15 by triedel           #+#    #+#             */
/*   Updated: 2024/05/31 01:42:28 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	while (*lst)
	{
		(*del)((*lst)->content);
		next = (*lst)->next;
		ft_free(*lst);
		*lst = next;
	}
}

t_list	*ft_lstclear_null(t_list **lst, void (*del)(void *))
{
	ft_lstclear(lst, del);
	return (NULL);
}
