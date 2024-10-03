/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:46:10 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/03 14:18:41 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprites(t_draw *draw, t_thread_params *params,
		t_sprite_coords sprites)
{
	t_texture		*tex;
	const t_player	*p = params->player;
	int				tex_x;
	int				start_y;
	float			tex_y;
	int				end_y;
	int				color;
	float			step;

	tex = sprites.sprite_tex[current_frame(sprites.frames)];
	tex_y = get_check(&start_y, &end_y, &step, sprites.height);
	tex_x = sprites.tex_x;
	while (start_y < end_y)
	{
		color = get_pixel_from_image(tex, tex_x, tex_y);
		color = darken_color_wall(color, (float)sprites.dist / 450, sprites.x
				/ BLOCK_SIZE, sprites.y / BLOCK_SIZE);
		if (color && color > 0)
			draw->colors[start_y] = color;
		tex_y += step;
		start_y++;
	}
}

void	draw_sprite(t_draw *draw, t_thread_params *params)
{
	if (draw->is_sprite)
		while (--draw->s_count >= 0)
			draw_sprites(draw, params, draw->sprites[draw->s_count]);
	if (draw->is_facing)
		while (--draw->f_count >= 0)
			draw_sprites(draw, params, draw->facing[draw->f_count]);
}
