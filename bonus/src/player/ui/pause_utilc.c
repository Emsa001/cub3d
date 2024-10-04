/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_utilc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 02:30:25 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 20:03:15 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resume_game(void *arg)
{
	t_cube		*c;
	t_player	*p;

	c = cube();
	p = player();
	p->mouse_hook = true;
	p->gui = NONE;
	pthread_mutex_lock(&c->pause_mutex);
	c->paused = false;
	pthread_mutex_unlock(&c->pause_mutex);
	(void)arg;
}

void	pause_hover(void *arg)
{
	const t_uitextures	*t = textures()->ui;
	const int			x = WIDTH / 2 - t->play->width / 2;
	const int			y = HEIGHT / 2 - t->play->height / 2;
	const int			new_x = x - (t->play_hover->width * 1.1
			- t->play_hover->width) / 2;
	const int			new_y = y - (t->play_hover->height * 1.1
			- t->play_hover->height) / 2;

	put_image(t->play_hover, new_x, new_y, 1.1);
	(void)arg;
}

static void	exit_hover(void *arg)
{
	const t_uitextures	*t = textures()->ui;
	const int			x = WIDTH / 2 + 205;
	const int			y = HEIGHT / 2 + 110;
	const int			new_x = x - (t->button_hover->width * 1.1
			- t->button_hover->width) / 2;
	const int			new_y = y - (t->button_hover->height * 1.1
			- t->button_hover->height) / 2;

	put_image(t->button_hover, new_x, new_y, 1.1);
	change_image_color(t->home, 0xE52554);
	put_image(t->home, WIDTH / 2 + 218, HEIGHT / 2 + 118, 1.1);
	tooltip("Exit :(", 0.5);
	(void)arg;
}

static void	exit_game_f(void *arg)
{
	(void)arg;
	exit_game(0);
}

void	exit_button(void)
{
	const t_uitextures	*t = textures()->ui;
	const int			x = WIDTH / 2 + 205;
	const int			y = HEIGHT / 2 + 110;
	t_button			button;

	put_image(t->button, x, y, 1);
	change_image_color(t->home, 0xFFFFFF);
	put_image(t->home, WIDTH / 2 + 220, HEIGHT / 2 + 120, 1);
	button.x = x;
	button.y = y;
	button.width = t->button->width;
	button.height = t->button->height;
	button.left_click = &exit_game_f;
	button.hover = &exit_hover;
	button.arg = (void *)1;
	button.is_default = false;
	add_button(&button);
}
