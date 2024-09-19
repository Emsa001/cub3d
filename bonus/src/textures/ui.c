/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:27:14 by escura            #+#    #+#             */
/*   Updated: 2024/09/19 16:18:05 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "textures.h"

void init_keys(t_textures *t){
	int i = 0;
	while(i < 32){
		t_texture *key = ft_malloc(sizeof(t_texture));

        char *name = "assets/keys/key";
        char *num = ft_itoa(i);
        char *ext = ".xpm";
        char *path = ft_strjoin(name, num);
        char *path2 = ft_strjoin(path, ext);

		key->image = get_texture_file(path2, &key->width, &key->height);
		key->data = mlx_get_data_addr(key->image, &key->bpp, &key->size_line, &key->endian);
		t->ui->keys[i] = key;
		i++;

		ft_free(num);
        ft_free(path);
        ft_free(path2);
	}
}

void init_ui(t_textures *t)
{
    t->ui = ft_malloc(sizeof(t_uitextures));

	t_texture *button = ft_malloc(sizeof(t_texture));
	button->image = get_texture_file("assets/UI/Button/Default.xpm", &button->width, &button->height);
	button->data = mlx_get_data_addr(button->image, &button->bpp, &button->size_line, &button->endian);
	t->ui->button = button;

	t_texture *button_hover = ft_malloc(sizeof(t_texture));
	button_hover->image = get_texture_file("assets/UI/Button/Hover.xpm", &button_hover->width, &button_hover->height);
	button_hover->data = mlx_get_data_addr(button_hover->image, &button_hover->bpp, &button_hover->size_line, &button_hover->endian);
	t->ui->button_hover = button_hover;

	t_texture *button_long = ft_malloc(sizeof(t_texture));
	button_long->image = get_texture_file("assets/UI/Button/Default_long.xpm", &button_long->width, &button_long->height);
	button_long->data = mlx_get_data_addr(button_long->image, &button_long->bpp, &button_long->size_line, &button_long->endian);
	t->ui->button_long = button_long;

	t_texture *play = ft_malloc(sizeof(t_texture));
	play->image = get_texture_file("assets/UI/Button/play/Default.xpm", &play->width, &play->height);
	play->data = mlx_get_data_addr(play->image, &play->bpp, &play->size_line, &play->endian);
	t->ui->play = play;

	t_texture *play_hover = ft_malloc(sizeof(t_texture));
	play_hover->image = get_texture_file("assets/UI/Button/play/Hover.xpm", &play_hover->width, &play_hover->height);
	play_hover->data = mlx_get_data_addr(play_hover->image, &play_hover->bpp, &play_hover->size_line, &play_hover->endian);
	t->ui->play_hover = play_hover;

	t_texture *window = ft_malloc(sizeof(t_texture));
	window->image = get_texture_file("assets/UI/Window/Big.xpm", &window->width, &window->height);
	window->data = mlx_get_data_addr(window->image, &window->bpp, &window->size_line, &window->endian);
	t->ui->window = window;

	t_texture *home = ft_malloc(sizeof(t_texture));
	home->image = get_texture_file("assets/UI/png/Icon/Home.xpm", &home->width, &home->height);
	home->data = mlx_get_data_addr(home->image, &home->bpp, &home->size_line, &home->endian);
	t->ui->home = home;

	t_texture *panel = ft_malloc(sizeof(t_texture));
	panel->image = get_texture_file("assets/UI/Window/Headless.xpm", &panel->width, &panel->height);
	panel->data = mlx_get_data_addr(panel->image, &panel->bpp, &panel->size_line, &panel->endian);
	t->ui->panel = panel;

	init_keys(t);
	init_progress(t);
}