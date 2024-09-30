/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:04:28 by escura            #+#    #+#             */
/*   Updated: 2024/09/30 16:09:38 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	init_potions(t_cube *c)
{
	const t_fullitem	weapons[] = {\
		{"Speed", 0.5, 169, NONE, 500, 5000, &player()->speed, &consume, NULL}, \
		{"Luck", 0.5, 170, NONE, 500, 5000, &player()->speed, &consume, NULL}, \
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
