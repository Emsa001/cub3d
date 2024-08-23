/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: triedel <triedel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:43:34 by triedel           #+#    #+#             */
/*   Updated: 2024/01/03 15:24:09 by triedel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *nnew)
{
	if (!lst || !nnew)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = nnew;
	else
		*lst = nnew;
}

void	ft_lstadd(t_list **lst, t_list *nnew)
{
	ft_lstadd_back(lst, nnew);
}
