/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:46:59 by escura            #+#    #+#             */
/*   Updated: 2025/08/16 14:40:23 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	buy_portal_tooltip(void *arg)
{
	tooltip("10000 $", 0.4);
	(void)arg;
}

static void	power_portal_info(void)
{
	t_string	str;

	str = (t_string){0};
	str.str = "You have powered up the portal!";
	str.x = WIDTH / 2 - 500;
	str.y = HEIGHT - 200;
	str.color = 0x00FF00;
	str.size = 1;
	str.time = 5000;
	render_string_async(&str);
}

static void	power_portal(void *arg)
{
	if (money() < 10000)
		return ;
	player()->gui = NONE;
	power_portal_info();
	cube()->next_portal -= 1;
	open_portal(cube()->next_portal);
	add_money(-10000);
	(void)arg;
}

void	portal_offer(int x, int y)
{
	const t_cube		*c = cube();
	const t_textures	*t = textures();
	t_button			button;

	if (c->next_portal == 0)
		return ;
	button = (t_button){0};
	button.x = x + t->ui->button->width * 3 + 25;
	button.y = y + 360;
	button.width = t->ui->button->width * 5 + 25;
	button.height = t->ui->button->height * 3;
	button.left_click = &power_portal;
	button.hover = &buy_portal_tooltip;
	if (!player()->store->portal_cooldown)
		add_button(&button);
	put_image(t->open_portal, button.x, button.y, 0.9);
}
