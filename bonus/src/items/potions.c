/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:04:28 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 20:39:24 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	init_potions(t_cube *c)
{
	const t_fullitem	potions[] = {
	{"Speed I", 0.5, 168, NONE, 100, 10000, &player()->speed, &consume, NULL},
	{"Speed II", 0.5, 169, NONE, 200, 10000, &player()->speed, &consume, NULL},
	{"Speed 1I", 0.5, 170, NONE, 300, 10000, &player()->speed, &consume, NULL},
	{"Speed 1V", 0.5, 171, NONE, 400, 10000, &player()->speed, &consume, NULL},
	{"Speed V", 0.5, 15, NONE, 500, 10000, &player()->speed, &consume, NULL},
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
