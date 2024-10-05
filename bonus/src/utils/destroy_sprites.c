/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:55:00 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 16:49:49 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_sprite_image(t_sprite sprite)
{
	int	i;

	i = 0;
	while (i < sprite.frames)
	{
		destroy_texture(sprite.sprite_tex[i]);
		i++;
	}
}

void	destroy_sprites(void)
{
	t_sprite *const	facing = cube()->map->facing;
	t_sprite *const	sprites = cube()->map->sprites;
	int				i;

	i = 0;
	while (facing[i].x != -1)
	{
		if (facing[i].sprite_tex != NULL)
			destroy_sprite_image(facing[i]);
		i++;
	}
	i = 0;
	while (sprites[i].x != -1)
	{
		if (sprites[i].sprite_tex != NULL)
			destroy_sprite_image(sprites[i]);
		i++;
	}
}
