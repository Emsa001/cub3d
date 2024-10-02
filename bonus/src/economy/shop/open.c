/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:22:47 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 22:51:06 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	store_window(int x, int y)
{
	const t_uitextures	*t = textures()->ui;
	t_string			str;

	put_image(t->window, x, y, 1.8);
	str = (t_string){0};
	str.str = "MARKET";
	str.color = 0x00FF00;
	str.size = 1.5;
	str.x = CENTER_WIDTH - 140;
	str.y = CENTER_HEIGHT - 320;
	render_string(&str);
}

static void	*buy_item(void *arg)
{
	const int	price = (int)arg;
	int			i;

	if (price > money())
	{
		printf("Not enough money\n");
		return (NULL);
	}
	i = 0;
	while (i < 9)
	{
		if (player()->inventory[i] == -1)
		{
			add_money(-price);
			player()->inventory[i] = player()->hover->item_id;
			return (NULL);
		}
		i++;
	}
	printf("Inventory full\n");
	return (NULL);
}

static void	init_shop_items(int x, int y)
{
	t_button	button;
	int			i;

	i = 0;
	while (i < 21)
	{
		if (player()->store->items[i] != -1)
		{
			button = (t_button){0};
			button.x = x + 10 + (i % 3) * 70;
			button.y = y + 160 + (i / 3) * 70;
			button.width = 64;
			button.height = 64;
			button.left_click = &buy_item;
			button.hover = &shop_item_hover;
			button.arg = player()->store->prices[i];
			button.item_id = player()->store->items[i];
			add_button(&button);
			item_button(&button, 0.8);
		}
		i++;
	}
}

void	open_store(void)
{
	const t_textures	*t = textures();
	const int			x = CENTER_WIDTH - t->ui->window->width * 1.8 / 2;
	const int			y = CENTER_HEIGHT - t->ui->window->height * 1.8 / 2;

	player()->mouse_hook = false;
	store_window(x, y);
	special_offer(x, y);
	init_cases(x, y);
	portal_offer(x, y);
	init_shop_items(x, y);
}
