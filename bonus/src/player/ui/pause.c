/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:30:48 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 17:19:57 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	change_quality(void *arg)
{
	int	quality;

	quality = (intptr_t)arg;
	printf("Quality: %d\n", quality);
	update_quality(render(), quality);
}

static void	quality_hover(void *arg)
{
	int	quality;

	quality = (intptr_t)arg;
	if (quality == 20)
		tooltip("Low Quality", 0.45);
	else if (quality == 5)
		tooltip("Medium Quality", 0.38);
	else if (quality == 1)
		tooltip("High Quality", 0.42);
}

static void	quality_settings(int x, int y)
{
	t_button	button;

	button = (t_button){0};
	button.x = x + 10;
	button.y = y + 100;
	button.is_default = true;
	button.left_click = &change_quality;
	button.hover = &quality_hover;
	button.arg = (void *)1;
	add_button(&button);
	button.y = y + 185;
	button.arg = (void *)5;
	add_button(&button);
	button.y = y + 270;
	button.arg = (void *)20;
	add_button(&button);
}

static void	put_window(void)
{
	t_uitextures *const	t = textures()->ui;
	const int			x = WIDTH / 2 - t->window->width / 2;
	const int			y = HEIGHT / 2 - t->window->height / 2;
	t_string			str;

	put_image(t->window, x, y, 1);
	str = (t_string){0};
	str.str = "PAUSED";
	str.color = 0x00FF00;
	str.size = 1.5;
	str.x = WIDTH / 2 - 140;
	str.y = HEIGHT / 2 - 190;
	render_string(&str);
	str.str = "Press    to resume";
	str.color = 0x00FF00;
	str.size = 0.5;
	str.x = WIDTH / 2 - 280;
	str.y = HEIGHT / 2 + 160;
	put_image(&(t->keys[1]), WIDTH / 2 - 210, HEIGHT / 2 + 150, 2.5);
	render_string(&str);
	exit_button();
	quality_settings(x, y);
}

void	pause_game(void)
{
	const t_uitextures	*t = textures()->ui;
	const int			x = WIDTH / 2 - t->play->width / 2;
	const int			y = HEIGHT / 2 - t->play->height / 2;
	t_button			button;

	button = (t_button){0};
	player()->gui = PAUSE;
	player()->mouse_hook = false;
	put_window();
	put_image(t->play, x, y, 1);
	button.x = x;
	button.y = y;
	button.width = t->play->width;
	button.height = t->play->height;
	button.left_click = &resume_game;
	button.hover = &pause_hover;
	button.arg = NULL;
	button.is_default = false;
	add_button(&button);
}
