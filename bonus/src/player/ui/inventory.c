/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:18:14 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 20:08:03 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

static void	hud_inventory_con(const t_player *p, int i, int x, int y)
{
	t_button	button;

	button = (t_button){0};
	if (p->equipped[i] != -1)
	{
		button.x = x + 25 + (i % 4) * 70;
		button.y = y + 25 + (i / 4) * 70;
		button.width = 64;
		button.height = 64;
		button.left_click = &unequip;
		button.arg = (void *)(intptr_t)i;
		button.hover = &item_tooltip;
		button.item_id = p->equipped[i];
		button.is_default = false;
		add_button(&button);
		put_image(&(textures()->items[p->equipped[i]]), x + 25 + (i % 4) * 70, y
			+ 25 + (i / 4) * 70, 1.5);
	}
}

void	hud_inventory(void)
{
	const t_player *p = player();
	const int		x = 10;
	const int		y = HEIGHT - textures()->inventory_player->height - 10;
	int				i;

	i = 0;
	put_image(textures()->inventory_player, x, y, 1);
	while (i < 8)
	{
		hud_inventory_con(p, i, x, y);
		i++;
	}
}

static void	open_inventory_con(t_player *p, int i, int x, int y)
{
	t_button	button;

	if (p->inventory[i] != -1)
	{
		put_image(&(textures()->items[p->inventory[i]]), x + 25 + (i % 3) * 70,
			y + 25 + (i / 3) * 70, 1.5);
		button.x = x + 25 + (i % 3) * 70;
		button.y = y + 25 + (i / 3) * 70;
		button.width = 64;
		button.height = 64;
		button.left_click = &use_item;
		button.hover = &item_tooltip;
		button.arg = (void *)(intptr_t)i;
		button.item_id = p->inventory[i];
		button.is_default = false;
		add_button(&button);
	}
}

void	open_inventory(void)
{
	t_player	*p;
	const int	x = (WIDTH / 2 - textures()->inventory_gui->width / 2);
	const int	y = (HEIGHT / 2 - textures()->inventory_gui->height / 2);
	t_string	str;
	int			i;

	p = player();
	p->mouse_hook = false;
	str = (t_string){0};
	str.str = "Inventory";
	str.color = 0xFFFFFF;
	str.size = 0.6;
	str.x = x;
	str.y = y - 25;
	render_string(&str);
	put_image(textures()->inventory_gui, x, y, 1);
	i = 0;
	while (i < 9)
	{
		open_inventory_con(p, i, x, y);
		i++;
	}
}
