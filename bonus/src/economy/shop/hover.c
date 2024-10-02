/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:04:55 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 17:32:35 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	shop_item_hover(void *arg)
{
	const int	price = (int)(intptr_t)player()->hover->arg;
	char		*price_str;
	char		*temp;

	if (price > money())
	{
		tooltip("Not enough money", 0.4);
		return ;
	}
	price_str = ft_itoa(price);
	temp = ft_strjoin("Buy for ", price_str);
	tooltip(temp, 0.4);
	ft_free(temp);
	ft_free(price_str);
}
