/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:04:28 by escura            #+#    #+#             */
/*   Updated: 2024/09/27 18:26:41 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

t_item	*init_item(char *name, double fontSize, int id, int effect, int time,
		int *intvar, void (*use)())
{
	t_item	*item;

	item = (t_item *)ft_calloc(sizeof(t_item), 1);
	item->name = name;
	item->fontSize = fontSize;
	item->props.id = id;
	item->props.effect = effect;
	item->props.time = time;
	item->props.intvar = intvar;
	item->use = use;
	return (item);
}

void	init_potions(t_cube *c)
{
	c->items[169] = *init_item("Speed", 0.5, 169, 500, 5000, &player()->speed,
			&consume);
	c->items[170] = *init_item("Luck", 0.5, 170, 500, 5000, &player()->speed,
			&consume);
}