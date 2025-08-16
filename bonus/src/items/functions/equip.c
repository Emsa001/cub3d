/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:27:00 by escura            #+#    #+#             */
/*   Updated: 2024/09/27 18:11:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	equip(t_itemprops props)
{
	t_player	*p;

	p = player();
	if (p->equipped[props.slot] != -1)
		return ;
	printf("Equipping item %d in slot %d\n", props.id, props.slot);
	p->inventory[props.playerslot] = -1;
	if (props.slot == BOOTS)
		p->speed += props.effect;
	else if (props.slot == WEAPON)
		p->hand = &cube()->items[props.id];
	p->equipped[props.slot] = props.id;
}
