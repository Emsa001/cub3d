/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:36:08 by escura            #+#    #+#             */
/*   Updated: 2024/10/07 15:29:43 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_texture(t_texture *texture)
{
	if (texture == NULL || texture->image == NULL || texture->data == NULL)
		return ;
	destroy_image(texture->image);
	ft_free(texture->data);
	ft_free(texture);
	texture = NULL;
}

void	destroy_ui(void)
{
	t_textures	*t;

	t = textures();
	destroy_texture(t->ui->button);
	destroy_texture(t->ui->button_hover);
	destroy_texture(t->ui->play);
	destroy_texture(t->ui->play_hover);
	destroy_texture(t->ui->window);
	destroy_texture(t->ui->home);
	destroy_texture(t->ui->panel);
}

void	destroy_texture_arr(t_texture **t)
{
	int	i;

	if (!t)
		return ;
	i = 0;
	while (i < 4)
	{
		destroy_texture(t[i]);
		i++;
	}
}

static void	destroy_textures_multiple(t_textures *t)
{
	int	i;

	i = 0;
	while (i < 328)
		destroy_texture(&(t->items[i++]));
	i = 0;
	while (i < 32)
		destroy_texture(&(t->ui->keys[i++]));
	i = 0;
	while (i < 24)
		destroy_texture(&(t->ui->progress[i++]));
	i = 0;
	while (i < 3)
		destroy_texture(&(t->ui->progress_cover[i++]));
	i = 0;
	while (i < 8)
		destroy_texture(&(t->ui->loading[i++]));
}

void	destroy_textures(void)
{
	t_textures *const	t = textures();

	if (!t)
		return ;
	destroy_texture_arr(t->wall_north);
	destroy_texture_arr(t->wall_south);
	destroy_texture_arr(t->wall_east);
	destroy_texture_arr(t->wall_west);
	destroy_texture_arr(t->ceiling);
	destroy_texture_arr(t->floor);
	destroy_texture(t->door);
	destroy_texture(t->generator[0]);
	destroy_texture(t->generator[1]);
	destroy_texture(t->generator_top);
	destroy_texture(t->font);
	destroy_texture(t->inventory_player);
	destroy_texture(t->inventory_gui);
	destroy_texture(t->tooltip_bg);
	destroy_texture(t->open_portal);
	if (!t->ui)
		return ;
	destroy_texture(t->ui->button_long);
	destroy_ui();
	destroy_textures_multiple(t);
}
