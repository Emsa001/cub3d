/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:30:48 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 02:33:03 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_window(void)
{
	const t_uitextures	*t = textures()->ui;
	const int			x = CENTER_WIDTH - t->window->width / 2;
	const int			y = CENTER_HEIGHT - t->window->height / 2;
	t_string			str;

	put_image(t->window, x, y, 1);
	str = (t_string){0};
	str.str = "PAUSED";
	str.color = 0x00FF00;
	str.size = 1.5;
	str.x = CENTER_WIDTH - 140;
	str.y = CENTER_HEIGHT - 190;
	render_string(&str);
	str.str = "Press    to resume";
	str.color = 0x00FF00;
	str.size = 0.5;
	str.x = CENTER_WIDTH - 280;
	str.y = CENTER_HEIGHT + 160;
	put_image(&(t->keys[1]), CENTER_WIDTH - 210, CENTER_HEIGHT + 150, 2.5);
	render_string(&str);
	exit_button();
}

void	pause_game(void)
{
	const t_uitextures	*t = textures()->ui;
	const int			x = CENTER_WIDTH - t->play->width / 2;
	const int			y = CENTER_HEIGHT - t->play->height / 2;
	t_button			button;

	player()->GUI = PAUSE;
	player()->mouse_hook = false;
	put_window();
	put_image(t->play, x, y, 1);
	button.x = x;
	button.y = y;
	button.width = t->play->width;
	button.height = t->play->height;
	button.function = &resume_game;
	button.hover = &pause_hover;
	button.arg = NULL;
	button.is_default = false;
	add_button(&button);
}
