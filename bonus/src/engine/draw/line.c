/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:46:18 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 10:33:38 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_scene(t_draw *draw, t_thread_params *params)
{
	const t_player	*p = params->player;
	float			step;
	int				wall_start_y;
	int				wall_end_y;
	int				y;
	int				color;
	t_texture		*tex;

	color = 0;
	step = (float)T_SIZE / draw->wall_height;
	wall_start_y = (params->player->z - 1) * draw->wall_height + HEIGHT / 2;
	wall_end_y = wall_start_y + draw->wall_height;
	if (wall_start_y < 0)
	{
		draw->tex_y = step * (-wall_start_y);
		wall_start_y = 0;
	}
	if (wall_end_y > HEIGHT)
		wall_end_y = HEIGHT;
	y = 0;
	while (y <= wall_start_y)
	{
		if(draw->colors[y] == 0)
		{
			float			current_dist;
			current_dist = view_current_distance(p, y, draw->angle);
			tex = params->textures->ceiling[p->level];
			color = get_texture_color(tex, current_dist, draw);
			if (color <= 0)
				color = 0;
			draw->colors[y] = color;
		}
		y++;
	}
	while (y <= wall_end_y)
	{
		if(draw->colors[y] == 0)
		{
			color = get_pixel_from_image(draw->texture, draw->tex_x, draw->tex_y);
			color = darken_color_wall(color, (float)draw->dist / 450, draw->x
					/ BLOCK_SIZE, draw->y / BLOCK_SIZE);
			if (color <= 0)
				color = 0;
			draw->tex_y += step;
			draw->colors[y] = color;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		if(draw->colors[y] == 0)
		{
			float			current_dist;
			current_dist = view_current_distance(p, y, draw->angle);
			tex = params->textures->floor[p->level];
			color = get_texture_color(tex, current_dist, draw);
			if (color <= 0)
				color = 0;
			draw->colors[y] = color;
		}
		y++;
	}
}

void draw_sprites(t_draw *draw, t_thread_params *params, t_sprite_coords sprites)
{
	t_texture *tex = sprites.sprite_tex[current_frame(sprites.frames)];
	const t_player *p = params->player;
	int start_y;
	float tex_y = 0;
	int end_y;
	float step = (float)T_SIZE / sprites.height;
	int color;
	start_y = (params->player->z - 1) * sprites.height + HEIGHT / 2;
	end_y = start_y + sprites.height;
	int tex_x = sprites.tex_x;

	if (start_y < 0)
	{
		tex_y = -start_y * step;
		start_y = 0;
	}
	if(end_y > HEIGHT)
		end_y = HEIGHT;

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

void init_sprite_coords(t_draw *draw)
{
	t_sprite_coords *sprites;
	const t_map *map = cube()->map;
	int i;
	
	i = 0;
	sprites = malloc(sizeof(t_sprite_coords) * map->sprite_count);
	while (i < map->sprite_count)
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
	draw->sprites = sprites;
}

t_draw	init_draw(void)
{
	t_draw	draw;

	init_sprite_coords(&draw);
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

int	touch_sprite(t_sprite *sprites, float px, float py)
{
	int		i;
	float	x;
	float	y;

	i = 0;
	x = 0;
	y = 0;
	if (!sprites)
		return 0;
	while (sprites[i].x != -1)
	{
		x = sprites[i].x * BLOCK_SIZE;
		y = sprites[i].y * BLOCK_SIZE;
		if (px >= x && px <= x + sprites[i].width && py >= y && py <= y + 1)
			return i + 1;
		i++;
	}
	return 0;
}

void	draw_line(t_draw draw, t_thread_params *params)
{
	t_cube	*c;
	int		scale;

	c = params->cube;
	draw.cosangle = cos(draw.angle);
	draw.sinangle = sin(draw.angle);
	int iter = 0;
	while (!find_hitbox(&draw, c, &iter))
	{
		draw.x += draw.cosangle;
		draw.y += draw.sinangle;
	}
	direction(&draw, params);
	draw.dist = lane_distance(&draw);
	draw.wall_height = (BLOCK_SIZE * HEIGHT) / draw.dist;
	draw_scene(&draw, params);
	if(draw.is_sprite)
		draw_sprites(&draw, params, draw.sprites[0]);

	scale = draw.start_x + WIDTH_SCALE;
	while (draw.start_x < scale && draw.start_x < params->end)
	{
		put_line(draw, params);
		draw.start_x++;
	}
}

// void	draw_line_old(t_draw draw, t_thread_params *params)
// {
// 	t_cube *c = params->cube;
// 	const t_player *p = params->player;
// 	float cosangle = cos(draw.angle);
// 	float sinangle = sin(draw.angle);

// 	bool save = false;
// 	bool save_last = false;

// 	t_float *touch = malloc(sizeof(t_float) * c->map->sprite_count);
// 	ft_bzero(touch, sizeof(t_float) * c->map->sprite_count);
// 	int i = 0;

// 	while (!find_hitbox(draw.x, draw.y, c))
// 	{
// 		if (touch_sprite(c->map->sprites, draw.x, draw.y)
// 			|| touch_facing_sprite(&draw, c->map->facing, draw.x, draw.y))
// 		{
// 			touch[i].x = draw.x;
// 			touch[i].y = draw.y;
// 			i++;
// 		}
// 		if (touch_generator(c->map->generators, draw.x, draw.y))
// 		{
// 			if (!save)
// 			{
// 				save = true;
// 				draw.first_x = draw.x;
// 				draw.first_y = draw.y;
// 			}
// 			draw.x += cosangle;
// 			draw.y += sinangle;
// 			if (!save_last && !touch_generator(c->map->generators, draw.x,
// 					draw.y))
// 			{
// 				save_last = true;
// 				draw.last_x = draw.x;
// 				draw.last_y = draw.y;
// 			}
// 		}
// 		else
// 		{
// 			draw.x += cosangle;
// 			draw.y += sinangle;
// 		}
// 	}

// 	draw.side = direction(draw.x, draw.y, cosangle, sinangle, c, &draw.tex_x);
// 	lane_distance(&draw);
// 	draw_scene(&draw, params);
// 	while (i > 0)
// 	{
// 		draw.sprite_x = touch[i].x;
// 		draw.sprite_y = touch[i].y;
// 		sprite_dist(&draw);
// 		int j = 0;
// 		if ((j = touch_sprite(c->map->sprites, draw.sprite_x, draw.sprite_y)))
// 		{
// 			draw.tex_x = (int)draw.sprite_x % BLOCK_SIZE;
// 			sprite_frame(&draw, params, c->map->sprites[j - 1]);
// 		}
// 		else if (touch_facing_sprite(&draw, c->map->facing, draw.sprite_x,
// 				draw.sprite_y))
// 			sprite_frame(&draw, params, c->map->facing[0]);
// 		i--;
// 	}
// 	if (generator_direction(&draw, cosangle, sinangle, c) == 7)
// 	{
// 		draw_generator_top(&draw, params, draw.angle);
// 		draw_generator(&draw, params, draw.tex_x, draw.angle);
// 	}
// 	int scale = draw.start_x + WIDTH_SCALE;
// 	while (draw.start_x < scale && draw.start_x < params->end)
// 	{
// 		put_line(draw, params);
// 		draw.start_x++;
// 	}
// 	free(touch);
// }