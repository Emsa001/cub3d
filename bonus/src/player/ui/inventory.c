/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:18:14 by escura            #+#    #+#             */
/*   Updated: 2024/09/30 15:47:29 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

static void	hud_inventory_con(t_player *p, int i, int x, int y)
{
	t_button	button;

	button = (t_button){0};
	if (p->equipped[i] != -1)
	{
		put_image(&(textures()->items[p->equipped[i]]), x + 25 + (i % 4) * 70, y
			+ 25 + (i / 4) * 70, 1.5);
		button.x = x + 25 + (i % 4) * 70;
		button.y = y + 25 + (i / 4) * 70;
		button.width = 64;
		button.height = 64;
		button.function = &unequip;
		button.arg = (void *)(intptr_t)i;
		button.hover = &item_tooltip;
		button.itemId = p->equipped[i];
		button.remove = true;
		button.is_default = false;
		add_button(&button);
	}
}

void	hud_inventory(void)
{
	const t_player	*p = player();
	const int		x = 10;
	const int		y = HEIGHT - textures()->inventoryPlayer->height - 10;
	int				i;
	t_button		button;

	i = 0;
	put_image(textures()->inventoryPlayer, x, y, 1);
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
		button.function = &use_item;
		button.hover = &item_tooltip;
		button.arg = (void *)(intptr_t)i;
		button.itemId = p->inventory[i];
		button.remove = true;
		button.is_default = false;
		add_button(&button);
	}
}

void	open_inventory(void)
{
	t_player	*p;
	const int	x = (WIDTH / 2 - textures()->inventoryGui->width / 2);
	const int	y = (HEIGHT / 2 - textures()->inventoryGui->height / 2);
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
	put_image(textures()->inventoryGui, x, y, 1);
	i = 0;
	while (i < 9)
	{
		open_inventory_con(p, i, x, y);
		i++;
	}
}
