/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:27:14 by escura            #+#    #+#             */
/*   Updated: 2024/09/24 21:25:17 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "textures.h"

void	init_keys(t_textures *t)
{
	int		i;
	char	*path;

	i = 0;
	while (i < 32)
	{
		path = get_texture_name("assets/keys/key", i);
		t->ui->keys[i] = *load_texture(path);
		i++;
		ft_free(path);
	}
}

void	init_ui(t_textures *t)
{
	t->ui = ft_malloc(sizeof(t_uitextures));
	t->ui->button = load_texture("assets/UI/Button/Default.xpm");
	t->ui->button_long = load_texture("assets/UI/Button/Default_long.xpm");
	t->ui->button_hover = load_texture("assets/UI/Button/Hover.xpm");
	t->ui->play = load_texture("assets/UI/Button/play/Default.xpm");
	t->ui->play_hover = load_texture("assets/UI/Button/play/Hover.xpm");
	t->ui->window = load_texture("assets/UI/Window/Big.xpm");
	t->ui->home = load_texture("assets/UI/png/Icon/Home.xpm");
	t->ui->panel = load_texture("assets/UI/Window/Headless.xpm");
	init_keys(t);
	init_progress(t);
}
