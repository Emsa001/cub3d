/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:46:10 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/03 11:44:02 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// void	sprite_frame(t_draw *draw, t_thread_params *params, t_sprite sprite)
// {
// 	int				color;
// 	float			tex_y;
// 	float			step;
// 	const t_player	*p = params->player;
// 	t_render		*r;
// 	int				dist;
// 	int				start_y;
// 	int				end_y;
// 	t_texture		*sprite_tex;

// 	color = params->color;
// 	tex_y = 0;
// 	step = ((float)T_SIZE) / draw->sprite_height;
// 	r = params->render;
// 	dist = draw->sprite_dist;
// 	start_y = (p->z - 1) * draw->sprite_height + vert_offset(p);
// 	end_y = start_y + draw->sprite_height;
// 	sprite_tex = sprite.sprite_tex[current_frame(sprite.frames)];
// 	if (end_y > HEIGHT)
// 		end_y = HEIGHT;
// 	if (start_y < 0)
// 	{
// 		tex_y = -start_y * step;
// 		start_y = 0;
// 	}
// 	while (start_y < end_y)
// 	{
// 		color = get_pixel_from_image(sprite_tex, draw->tex_x, tex_y);
// 		color = darken_color_wall(color, (float)dist / 450, draw->sprite_x
// 				/ BLOCK_SIZE, draw->sprite_y / BLOCK_SIZE);
// 		if (color && color > 0)
// 			draw->colors[start_y] = color;
// 		tex_y += step;
// 		start_y++;
// 	}
// }

// bool	touch_facing(t_draw *draw, float px, float py, float sprite_x,
// 		float sprite_y, int width)
// {
// 	float	cosangle;
// 	float	sinangle;
// 	float	u;
// 	float	v;
// 	float	dist;

// 	// it's the same as cos(angle + 90)
// 	cosangle = cos(player()->angle);
// 	// it's the same as sin(angle + 90)
// 	sinangle = sin(player()->angle);
// 	u = (cosangle * (sprite_x - px) + sinangle * (sprite_y - py));
// 	if (u < 0 || u > 2)
// 		return false;
// 	v = (-sinangle * (sprite_x - px) + cosangle * (sprite_y - py));
// 	draw->tex_x = (int)v + width / 2;
// 	dist = distance(px, py, sprite_x, sprite_y);
// 	if (dist * 2 < width)
// 		return true;
// 	return false;
// }

// bool	touch_facing_sprite(t_draw *draw, t_sprite *sprites, float px, float py)
// {
// 	int		i;
// 	float	x;
// 	float	y;
// 	int		width;

// 	i = 0;
// 	x = 0;
// 	y = 0;
// 	if (!sprites)
// 		return false;
// 	while (sprites[i].x != -1)
// 	{
// 		x = sprites[i].x * BLOCK_SIZE;
// 		y = sprites[i].y * BLOCK_SIZE;
// 		width = sprites[i].width;
// 		if (touch_facing(draw, px, py, x, y, width))
// 			return true;
// 		i++;
// 	}
// 	return false;
// }

// void	sprite_dist(t_draw *draw)
// {
// 	float	x2;
// 	float	y2;
// 	float	player_angle;
// 	float	raw_distance;
// 	float	adjusted_distance;

// 	x2 = player()->x_px;
// 	y2 = player()->y_px;
// 	player_angle = player()->angle;
// 	raw_distance = distance(draw->sprite_x, draw->sprite_y, x2, y2);
// 	adjusted_distance = raw_distance * cos(player_angle - draw->angle);
// 	draw->sprite_dist = adjusted_distance;
// 	draw->sprite_height = (BLOCK_SIZE * HEIGHT) / adjusted_distance;
// }

