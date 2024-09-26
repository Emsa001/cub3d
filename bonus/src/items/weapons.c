/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:59:10 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 19:27:52 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	init_weapons(t_cube *c)
{
	const t_fullitem	weapons[] = {\
		{"Wooden Sword", 273, WEAPON, 10, &equip, NULL}, \
		{"Stone Sword", 275, WEAPON, 10, &equip, NULL}, \
		{"Pirate Sword", 279, WEAPON, 10, &equip, NULL}, \
		{"Axe", 24, WEAPON, 10, &equip, NULL}, \
		{"Torch", 33, WEAPON, 10, &equip, &place}, \
		{"Dagger", 282, WEAPON, 10, &equip, NULL}, \
		NULL
	};
	int					i;

	i = 0;
	while (weapons[i].name != NULL)
	{
		c->items[weapons[i].id] = *create_item(&weapons[i]);
		i++;
	}
}
