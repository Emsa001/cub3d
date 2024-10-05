/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:46:59 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 17:22:02 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	opening(void *arg)
{
	open_portal(cube()->next_portal);
	player()->store->portal_cooldown = false;
	(void)arg;
}

static void	buy_portal_tooltip(void *arg)
{
	tooltip("10000 $", 0.4);
	(void)arg;
}

static void	power_portal_info(int time)
{
	t_string			str;
	t_image				img;
	t_texture *const	t = textures()->ui->button_long;
	int					i;

	str = (t_string){0};
	str.str = "You have powered up the portal!";
	str.x = WIDTH / 2 - 500;
	str.y = HEIGHT - 200;
	str.color = 0x00FF00;
	str.size = 1;
	str.time = time;
	render_string_async(&str);
	i = 0;
	while (i < 5)
	{
		img = (t_image){0};
		img.img = t;
		img.x = WIDTH / 2 - 555 + (i * t->width - ((i - 1) * 4));
		img.y = HEIGHT - 225;
		img.size = 1;
		img.time = time - 100;
		render_image_async(&img);
		i++;
	}
}

static void	power_portal(void *arg)
{
	const int			time = 5000;
	t_location *const	loc = ft_calloc(1, sizeof(t_location));

	if (money() < 10000)
		return ;
	loc->x = WIDTH / 2 - 32;
	loc->y = HEIGHT / 2 - 32;
	player()->store->portal_cooldown = true;
	string_timer(time, loc);
	player()->gui = NONE;
	power_portal_info(time);
	ft_wait(time, &opening, NULL);
	add_money(-10000);
	(cube()->next_portal)--;
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
	if(!player()->store->portal_cooldown)
		add_button(&button);
	put_image(t->open_portal, button.x, button.y, 0.9);
}
