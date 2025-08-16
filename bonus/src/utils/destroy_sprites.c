/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:55:00 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 20:01:31 by escura           ###   ########.fr       */
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
	t_sprite	*facing;
	t_sprite	*sprites;
	int			i;

	if (cube()->map && cube()->map->facing)
	{
		facing = cube()->map->facing;
		i = 0;
		while (facing[i].x != -1)
			if (facing[i].sprite_tex != NULL)
				destroy_sprite_image(facing[i++]);
	}
	if (cube()->map && cube()->map->sprites)
	{
		sprites = cube()->map->sprites;
		i = 0;
		while (sprites[i].x != -1)
			if (sprites[i].sprite_tex != NULL)
				destroy_sprite_image(sprites[i++]);
	}
}
