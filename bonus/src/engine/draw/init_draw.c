/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:23:37 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/03 19:47:52 by escura           ###   ########.fr       */
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

t_gen_coords	init_gen_coords(void)
{
	t_gen_coords	gen;

	gen.dist = 0;
	gen.save = false;
	gen.first_x = 0;
	gen.first_y = 0;
	gen.last_x = 0;
	gen.last_y = 0;
	gen.first_tex_x = 0;
	gen.last_tex_x = 0;
	gen.height = 0;
	gen.height_top = 0;
	gen.tall = 0.6;
	gen.top = gen.tall - 0.12;
	return (gen);
}

t_draw	init_draw(void)
{
	t_draw	draw;

	draw.sprites = init_sprite_coords(cube()->map->sprite_count);
	draw.facing = init_sprite_coords(MAX_TORCHES);
	draw.gen = init_gen_coords();
	draw.s_count = 0;
	draw.f_count = 0;
	draw.x = player()->x_px;
	draw.y = player()->y_px;
	draw.is_sprite = false;
	draw.is_facing = false;
	draw.height = 0;
	draw.start_x = 0;
	draw.start_y = 0;
	draw.tex_x = 0;
	draw.tex_y = 0;
	draw.angle = 0;
	draw.dist = 0;
	draw.texture = NULL;
	draw.cosangle = 0;
	draw.sinangle = 0;
	ft_bzero(draw.colors, (HEIGHT + 1) * sizeof(int));
	return (draw);
}
