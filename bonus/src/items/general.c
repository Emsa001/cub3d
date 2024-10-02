/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:04:34 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 18:20:00 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	try_open_door(t_item *item)
{
	t_cube		*c;
	t_player	*p;

	c = cube();
	p = player();
	printf("Trying to open door with %s\n", item->name);
}

void	init_keys_items(t_cube *c)
{
	t_item	*item;

	item = (t_item *)ft_calloc(sizeof(t_item), 1);
	item->name = "Old Key";
	item->font_size = 0.5;
	item->props.id = 50;
	item->right_click = &try_open_door;
	c->items[50] = *item;
}
