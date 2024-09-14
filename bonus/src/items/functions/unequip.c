/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unequip.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:27:00 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 14:19:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	unequip(void *props)
{
	t_player *p = player();
	int index = (int)(intptr_t)props;
	t_item item = cube()->items[p->equipped[index]];

	printf("Unequipping item %d\n", index);

	int i = 0;
	while (i < 9)
	{
		if (p->inventory[i] == -1)
		{
			p->inventory[i] = p->equipped[index];
			break ;
		}
		i++;
	}

	if (i == 9)
	{
		printf("Inventory is full\n");
		return ;
	}

	if (index == BOOTS)
		p->speed -= item.props.effect;
	else if (index == WEAPON)
		p->hand = NULL;

	p->equipped[index] = -1;
}