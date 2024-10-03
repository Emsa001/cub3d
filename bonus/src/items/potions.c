/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:04:28 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 18:48:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	init_potions(t_cube *c)
{
	const t_fullitem potions[] = {
		{"Speed", 0.5, 169, NONE, 500, 5000, &player()->speed, &consume, NULL},
		{"Luck", 0.5, 170, NONE, 500, 5000, &player()->speed, &consume, NULL},
		{NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL}
	};
	int					i;

	i = 0;
	while (potions[i].name != NULL)
	{
		c->items[potions[i].id] = *create_item(&potions[i]);
		i++;
	}
}
