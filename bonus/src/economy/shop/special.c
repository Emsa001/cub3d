/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:06:59 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 18:19:05 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_correct_true(t_player *p, int arg, t_string str)
{
	int	multiplier;

	p->math_selected = 0;
	p->streak++;
	str.str = "CORRECT!";
	str.x -= 50;
	multiplier = p->streak;
	if (multiplier > 5)
		multiplier = 5;
	add_money(arg*multiplier);
	render_string_async(&str);
}

static void	is_correct(void *arg)
{
	t_string		str;
	t_player *const	p = player();

	p->gui = NONE;
	set_paused(false);
	str = (t_string){0};
	str.color = 0x00FF00;
	str.size = 2;
	str.x = CENTER_WIDTH - 150;
	str.y = CENTER_HEIGHT - 100;
	str.time = 500;
	str.background = 0x000001;
	str.padding = 10;
	if (p->math_selected == p->math[0] + p->math[1])
		return (is_correct_true(p, (intptr_t)arg, str));
	str.color = 0xFF0000;
	str.str = "WRONG!";
	render_string_async(&str);
	p->streak = 0;
}

static void	activate_special_timer(void *arg)
{
	t_texture	*window;
	int			x;
	int			y;
	t_location	*location;

	window = textures()->ui->window;
	x = CENTER_WIDTH - window->width / 2;
	y = CENTER_HEIGHT - window->height / 2;
	location = ft_malloc(sizeof(t_location));
	location->x = CENTER_WIDTH - 32;
	location->y = y - 200;
	string_timer(3000, location);
	set_paused(true);
	ft_wait(3000, &is_correct, arg);
}

void	activate_special(void *arg)
{
	t_player	*p;
	const int	rand_choice = random_int(0, 2);

	p = player();
	if (p->money < (intptr_t)arg)
	{
		printf("Not enough money!");
		return ;
	}
	add_money(-(intptr_t)arg);
	p->gui = MATH;
	p->math[0] = random_int(1, 100);
	p->math[1] = random_int(1, 100);
	p->random[0] = p->math[0] + p->math[1] + random_int(-5, 30);
	p->random[1] = p->math[0] + p->math[1] + random_int(-10, 10);
	p->random[2] = p->math[0] + p->math[1] + random_int(-20, 20);
	if (rand_choice == 0)
		p->random[0] = p->math[0] + p->math[1];
	else if (rand_choice == 1)
		p->random[1] = p->math[0] + p->math[1];
	else
		p->random[2] = p->math[0] + p->math[1];
	activate_special_timer(arg);
}

void	special_offer(int x, int y)
{
	const t_textures	*t = textures();
	const t_player		*p = player();
	const int			prices[2] = {1000, 10000};
	t_button			button;
	int					i;

	i = 0;
	while (i < 2)
	{
		button = (t_button){0};
		button.x = x + 810;
		button.y = y + 160 + i * t->ui->button->height * 3.2;
		button.width = t->ui->button->width * 3.2;
		button.height = t->ui->button->height * 3.2;
		button.left_click = &activate_special;
		button.hover = &shop_item_hover;
		button.arg = (void *)(intptr_t)prices[i];
		button.item_id = p->store->math[i];
		add_button(&button);
		item_button(&button, 3.2);
		i++;
	}
}
