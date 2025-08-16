/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unequip.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:27:00 by escura            #+#    #+#             */
/*   Updated: 2024/09/27 18:24:02 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	unequip(void *props)
{
	const int		index = (int)(intptr_t)props;
	const t_item	item = cube()->items[player()->equipped[index]];
	int				i;

	printf("Unequipping item %d\n", index);
	i = 0;
	while (i < 9)
	{
		if (player()->inventory[i] == -1)
		{
			player()->inventory[i] = player()->equipped[index];
			break ;
		}
		i++;
	}
	if (i == 9)
		return ;
	if (index == BOOTS)
		player()->speed -= item.props.effect;
	else if (index == WEAPON)
		player()->hand = NULL;
	player()->equipped[index] = -1;
}
