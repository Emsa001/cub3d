/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:30:48 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 00:28:04 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void change_quality(void *arg)
{
	int quality = (int)arg;
	printf("Quality: %d\n", quality);
	update_quality(render(), quality);
}

static void quality_hover(void *arg){
	int quality = (int)arg;
	if(quality == 20)
		tooltip("Low Quality",0.45);
	else if(quality == 5)
		tooltip("Medium Quality",0.38);
	else if(quality == 1)
		tooltip("High Quality",0.42);
}

static void quality_settings(int x, int y)
{
	t_button button = {0};
	button.x = x + 10;
	button.y = y + 100;
	button.is_default = true;
	button.left_click = &change_quality;
	button.hover = &quality_hover;
	button.arg = 1;
	add_button(&button);

	button.y = y + 185;
	button.arg = 5;
	add_button(&button);

	button.y = y + 270;
	button.arg = 20;
	add_button(&button);
}

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
	quality_settings(x,y);
}

void	pause_game(void)
{
	const t_uitextures	*t = textures()->ui;
	const int			x = CENTER_WIDTH - t->play->width / 2;
	const int			y = CENTER_HEIGHT - t->play->height / 2;
	t_button			button;

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
