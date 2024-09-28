/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:46:18 by escura            #+#    #+#             */
/*   Updated: 2024/09/28 14:12:04 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	direction(float x, float y, float cosangle, float sinangle, t_cube *c,
		int *tex_x)
{
	int	sx;
	int	sy;

	sx = cosangle > 0 ? 1 : -1;
	sy = sinangle > 0 ? 1 : -1;
	if (is_touching(x - sx, y, c) || is_touching(x - sx, y - sy, c))
	{
		*tex_x = (int)x % BLOCK_SIZE;
		return ((sy == 1) ? 1 : 3);
	}
	else if (is_touching(x, y - sy, c) || is_touching(x, y, c))
	{
		*tex_x = (int)y % BLOCK_SIZE;
		return ((sx == 1) ? 2 : 4);
	}
	else if (touch_block(c->map->doors, x - sx, y))
	{
		*tex_x = (int)x % BLOCK_SIZE;
		return (5);
	}
	else if (touch_block(c->map->doors, x, y - sy))
	{
		*tex_x = (int)y % BLOCK_SIZE;
		return (5);
	}
	else if (touch_block(c->map->blocks, x - sx, y))
	{
		*tex_x = (int)x % BLOCK_SIZE;
		return (6);
	}
	else if (touch_block(c->map->blocks, x, y))
	{
		*tex_x = (int)y % BLOCK_SIZE;
		return (6);
	}
	else if (touch_line(c->map->lines, x, y) == 1)
	{
		*tex_x = (int)x % BLOCK_SIZE;
		return (3);
	}
	else if (touch_line(c->map->lines, x, y) == 2)
	{
		*tex_x = (int)y % BLOCK_SIZE;
		return (1);
	}
	return (0);
}

int	generator_direction(t_draw *draw, float cosangle, float sinangle, t_cube *c)
{
	int	sx;
	int	sy;

	sx = 0;
	sy = 0;
	if (cosangle > 0)
		sx = 1;
	else
		sx = -1;
	if (sinangle > 0)
		sy = 1;
	else
		sy = -1;
	if (touch_generator(c->map->generators, draw->first_x - sx, draw->first_y))
	{
		draw->tex_x = (int)draw->first_x % BLOCK_SIZE;
		return (7);
	}
	else if (touch_generator(c->map->generators, draw->first_x, draw->first_y))
	{
		draw->tex_x = (int)draw->first_y % BLOCK_SIZE;
		return (7);
	}
	return (0);
}

static bool	find_hitbox(float x, float y, t_cube *c)
{
	if (is_touching(x, y, c))
		return (true);
	if (touch_block(c->map->blocks, x, y))
		return (true);
	if (touch_block(c->map->doors, x, y))
		return (true);
	if (touch_line(c->map->lines, x, y))
		return (true);
	return false;
}

t_draw	init_draw(void)
{
	t_draw	draw;

	draw.x = player()->x_px;
	draw.y = player()->y_px;
	draw.first_x = 0;
	draw.first_y = 0;
	draw.last_x = 0;
	draw.last_y = 0;
	draw.wall_height = 0;
	draw.height = 0;
	draw.height_top = 0;
	draw.start_x = 0;
	draw.start_y = 0;
	draw.side = 0;
	draw.tex_x = 0;
	draw.angle = 0;
	draw.dist = 0;
	draw.generator_dist = 0;
	draw.sprite_x = 0;
	draw.sprite_y = 0;
	draw.sprite_height = 0;
	draw.sprite_dist = 0;
	return draw;
}

long	current_frame(int frames)
{
	struct timeval	tv;
	int				time_delay;
	long			curr_time;
	int				curr_frame;

	gettimeofday(&tv, NULL);
	time_delay = 1000 / frames;
	if (frames == 28)
		time_delay = 90;
	if (frames == 5)
		time_delay = 60;
	if (frames == 2)
		time_delay = 150;
	curr_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	curr_frame = (curr_time / time_delay) % frames;
	return curr_frame;
}

void	put_line(t_draw draw, ThreadParams *params)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	end = HEIGHT;
	i = 0;
	while (start < end)
	{
		put_pixel(draw.start_x, start, draw.colors[start], params->render);
		start++;
	}
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
		if (px >= x && px <= x + sprites[i].width && py >= y && py <= y + 5)
			return i + 1;
		i++;
	}
	return 0;
}

void	sprite_frame(t_draw *draw, ThreadParams *params, t_sprite sprite)
{
	int				color;
	float			tex_y;
	float			step;
	const t_player	*p = params->player;
	t_render		*r;
	int				dist;
	int				start_y;
	int				end_y;
	t_texture		*sprite_tex;

	color = params->color;
	tex_y = 0;
	step = ((float)T_SIZE) / draw->sprite_height;
	r = params->render;
	dist = draw->sprite_dist;
	start_y = (p->z - 1) * draw->sprite_height + vert_offset(p);
	end_y = start_y + draw->sprite_height;
	sprite_tex = sprite.sprite_tex[current_frame(sprite.frames)];
	if (end_y > HEIGHT)
		end_y = HEIGHT;
	if (start_y < 0)
	{
		tex_y = -start_y * step;
		start_y = 0;
	}
	while (start_y < end_y)
	{
		color = get_pixel_from_image(sprite_tex, draw->tex_x, tex_y);
		color = darken_color_wall(color, (float)dist / 450, draw->sprite_x
				/ BLOCK_SIZE, draw->sprite_y / BLOCK_SIZE);
		if (color && color > 0)
			draw->colors[start_y] = color;
		tex_y += step;
		start_y++;
	}
}

bool	touch_facing(t_draw *draw, float px, float py, float sprite_x,
		float sprite_y, int width)
{
	float	cosangle;
	float	sinangle;
	float	u;
	float	v;
	float	dist;

	// it's the same as cos(angle + 90)
	cosangle = cos(player()->angle);
	// it's the same as sin(angle + 90)
	sinangle = sin(player()->angle);
	u = (cosangle * (sprite_x - px) + sinangle * (sprite_y - py));
	if (u < 0 || u > 2)
		return false;
	v = (-sinangle * (sprite_x - px) + cosangle * (sprite_y - py));
	draw->tex_x = (int)v + width / 2;
	dist = distance(px, py, sprite_x, sprite_y);
	if (dist * 2 < width)
		return true;
	return false;
}

bool	touch_facing_sprite(t_draw *draw, t_sprite *sprites, float px, float py)
{
	int		i;
	float	x;
	float	y;
	int		width;

	i = 0;
	x = 0;
	y = 0;
	if (!sprites)
		return false;
	while (sprites[i].x != -1)
	{
		x = sprites[i].x * BLOCK_SIZE;
		y = sprites[i].y * BLOCK_SIZE;
		width = sprites[i].width;
		if (touch_facing(draw, px, py, x, y, width))
			return true;
		i++;
	}
	return false;
}

void	sprite_dist(t_draw *draw)
{
	float	x2;
	float	y2;
	float	player_angle;
	float	raw_distance;
	float	adjusted_distance;

	x2 = player()->x_px;
	y2 = player()->y_px;
	player_angle = player()->angle;
	raw_distance = distance(draw->sprite_x, draw->sprite_y, x2, y2);
	adjusted_distance = raw_distance * cos(player_angle - draw->angle);
	draw->sprite_dist = adjusted_distance;
	draw->sprite_height = (BLOCK_SIZE * HEIGHT) / adjusted_distance;
}

void	draw_line(t_draw draw, ThreadParams *params)
{
	t_cube *c = params->cube;
	const t_player *p = params->player;
	float cosangle = cos(draw.angle);
	float sinangle = sin(draw.angle);

	bool save = false;
	bool save_last = false;

	t_touch *touch = malloc(sizeof(t_touch) * c->map->sprite_count);
	ft_bzero(touch, sizeof(t_touch) * c->map->sprite_count);
	int i = 0;

	while (!find_hitbox(draw.x, draw.y, c))
	{
		if (touch_sprite(c->map->sprites, draw.x, draw.y)
			|| touch_facing_sprite(&draw, c->map->facing, draw.x, draw.y))
		{
			touch[i].x = draw.x;
			touch[i].y = draw.y;
			i++;
		}
		if (touch_generator(c->map->generators, draw.x, draw.y))
		{
			if (!save)
			{
				save = true;
				draw.first_x = draw.x;
				draw.first_y = draw.y;
			}
			draw.x += cosangle;
			draw.y += sinangle;
			if (!save_last && !touch_generator(c->map->generators, draw.x,
					draw.y))
			{
				save_last = true;
				draw.last_x = draw.x;
				draw.last_y = draw.y;
			}
		}
		else
		{
			draw.x += cosangle;
			draw.y += sinangle;
		}
	}

	draw.side = direction(draw.x, draw.y, cosangle, sinangle, c, &draw.tex_x);
	lane_distance(&draw);
	draw_scene(&draw, params);
	while (i > 0)
	{
		draw.sprite_x = touch[i].x;
		draw.sprite_y = touch[i].y;
		sprite_dist(&draw);
		int j = 0;
		if ((j = touch_sprite(c->map->sprites, draw.sprite_x, draw.sprite_y)))
		{
			draw.tex_x = (int)draw.sprite_x % BLOCK_SIZE;
			sprite_frame(&draw, params, c->map->sprites[j - 1]);
		}
		else if (touch_facing_sprite(&draw, c->map->facing, draw.sprite_x,
				draw.sprite_y))
			sprite_frame(&draw, params, c->map->facing[0]);
		i--;
	}
	if (generator_direction(&draw, cosangle, sinangle, c) == 7)
	{
		draw_generator_top(&draw, params, draw.angle);
		draw_generator(&draw, params, draw.tex_x, draw.angle);
	}
	int scale = draw.start_x + WIDTH_SCALE;
	while (draw.start_x < scale)
	{
		put_line(draw, params);
		draw.start_x++;
	}
	free(touch);
}