/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:23:37 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/03 14:24:31 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite_coords	*init_sprite_coords(int count)
{
	t_sprite_coords	*sprites;
	int				i;

	i = 0;
	sprites = malloc(sizeof(t_sprite_coords) * count);
	ft_bzero(sprites, sizeof(t_sprite_coords) * count);
	while (i < count)
	{
		sprites[i].x = 0;
		sprites[i].y = 0;
		sprites[i].dist = 0;
		sprites[i].height = 0;
		sprites[i].tex_x = 0;
		sprites[i].sprite_tex = NULL;
		sprites[i].frames = 0;
		i++;
	}
	return (sprites);
}

t_draw	init_draw(void)
{
	t_draw	draw;

	draw.sprites = init_sprite_coords(cube()->map->sprite_count);
	draw.facing = init_sprite_coords(100);
	draw.s_count = 0;
	draw.f_count = 0;
	draw.x = player()->x_px;
	draw.y = player()->y_px;
	draw.is_sprite = false;
	draw.first_x = 0;
	draw.first_y = 0;
	draw.last_x = 0;
	draw.last_y = 0;
	draw.wall_height = 0;
	draw.height = 0;
	draw.height_top = 0;
	draw.start_x = 0;
	draw.start_y = 0;
	draw.tex_x = 0;
	draw.tex_y = 0;
	draw.angle = 0;
	draw.dist = 0;
	draw.generator_dist = 0;
	draw.texture = NULL;
	draw.cosangle = 0;
	draw.sinangle = 0;
	ft_bzero(draw.colors, (HEIGHT + 1) * sizeof(int));
	return (draw);
}
