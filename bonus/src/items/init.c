/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:16:29 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 19:24:35 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	init_items(void)
{
	t_cube	*c;

	c = cube();
	init_armor(c);
	init_potions(c);
	init_weapons(c);
	init_keys_items(c);
}

void	useItem(void *arg)
{
	int		index;
	int		id;
	t_item	i;

	index = (int)(intptr_t)arg;
	id = player()->inventory[index];
	i = cube()->items[id];
	i.props.playerslot = index;
	if (i.use != NULL)
		i.use(i.props);
}

void	item_tooltip(void *arg)
{
	t_player	*p;
	int			index;
	t_item		*item;

	p = player();
	index = p->hover->itemId;
	item = &cube()->items[index];
	tooltip(item->name, item->fontSize);
}

t_item	*create_item(const t_fullitem *props)
{
	t_item	*item;

	item = (t_item *)ft_calloc(1, sizeof(t_item));
	item->name = ft_strdup(props->name);
	item->fontSize = 0.4;
	item->use = props->use;
	item->right_click = props->right_click;
	item->props.id = props->id;
	item->props.slot = props->slot;
	item->props.effect = props->effect;
	item->props.playerslot = 0;
	return (item);
}
