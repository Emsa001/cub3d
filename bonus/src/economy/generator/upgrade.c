/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upgrade.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:37:28 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 18:23:00 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	buy_upgrade(void *arg)
{
	t_generator_upgrade	*upgrade;
	t_generator *const	gen = player()->generator;

	upgrade = (t_generator_upgrade *)arg;
	if (player()->money < upgrade->price
		|| *upgrade->level >= upgrade->max_level)
		return ;
	add_money(-upgrade->price);
	pthread_mutex_lock(&gen->mutex);
	if (upgrade->type)
		*upgrade->type += upgrade->prize;
	if (upgrade->level)
		*upgrade->level += 1;
	pthread_mutex_unlock(&gen->mutex);
}

static void	upgrade_hover(void *arg)
{
	t_generator_upgrade *const	upgrade = (t_generator_upgrade *)arg;

	if (!upgrade || !upgrade->name)
		return ;
	tooltip(upgrade->name, 0.5);
}

static void	upgrade_button(t_generator_upgrade *upgrade, int btn_x, int btn_y)
{
	t_texture *const	cover = progress_bar(1, PROGRESS_COVER);
	t_texture *const	progress = progress_bar(*upgrade->level, PROGRESS_RED);
	t_button			button;

	if (!cover || !progress)
		return ;
	if (upgrade->max_level > *upgrade->level)
	{
		button = (t_button){0};
		button.x = btn_x;
		button.y = btn_y;
		button.size = 0.3;
		button.left_click = &buy_upgrade;
		button.hover = &upgrade_hover;
		button.arg = (void *)upgrade;
		button.hover_change = true;
		button.is_default = true;
		add_button(&button);
	}
	put_image(cover, btn_x - 100, btn_y - 3, 2);
	put_image(progress, btn_x - 100, btn_y - 3, 2);
}

void	generator_upgrade(int x, int y, t_generator_upgrade *upgrade)
{
	char		*price_str;
	t_string	str;

	upgrade_button(upgrade, x + 120, y + 300);
	if (upgrade->max_level > *upgrade->level)
		price_str = ft_strjoin_itoa("Price: ", upgrade->price);
	else
		price_str = ft_strdup("Max level");
	str = (t_string){0};
	str.str = price_str;
	str.color = 0x00FF00;
	str.size = 0.4;
	str.x = x + 25;
	str.y = y + 300 - 20;
	render_string(&str);
	ft_free(price_str);
}
