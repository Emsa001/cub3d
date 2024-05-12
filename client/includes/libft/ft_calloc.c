/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:00:00 by triedel           #+#    #+#             */
/*   Updated: 2024/05/03 20:50:03 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*mem;

	mem = ft_malloc(nitems * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, nitems * size);
	return (mem);
}

void	*ft_setalloc(size_t num, size_t size, int value)
{
	void	*res;

	res = malloc(num * size);
	if (res)
		ft_memset(res, (unsigned char) value, num * size);
	return (res);
}
