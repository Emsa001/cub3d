/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:59:10 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 18:49:09 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	init_weapons(t_cube *c)
{
	const t_fullitem	weapons[] = {\
		{"Wooden Sword",	0.4, 273,	WEAPON, 10, 0, NULL, &equip, NULL}, \
		{"Stone Sword",		0.4, 275,	WEAPON, 10, 0, NULL, &equip, NULL}, \
		{"Pirate Sword",	0.4, 279,	WEAPON, 10, 0, NULL, &equip, NULL}, \
		{"Axe",				0.5, 24,	WEAPON, 10, 0, NULL, &equip, NULL}, \
		{"Torch",			0.5, 33,	WEAPON, 10, 0, NULL, &equip, &place}, \
		{"Dagger",			0.4, 282,	WEAPON, 10, 0, NULL, &equip, NULL}, \
		{NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL}
	};
	int					i;

	i = 0;
	while (weapons[i].name != NULL)
	{
		c->items[weapons[i].id] = *create_item(&weapons[i]);
		i++;
	}
}
