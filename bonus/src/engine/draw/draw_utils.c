/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:25:20 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/03 10:24:56 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (curr_frame);
}


void	put_line(t_draw draw, t_thread_params *params)
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

void get_sprite_coordinates(t_draw *draw, int i, int *iter)
{
	// i is the index of the sprite in the array
	draw->sprites[(*iter)].x = draw->x;
	draw->sprites[(*iter)].y = draw->y;
	draw->sprites[(*iter)].dist = lane_distance(draw);
	draw->sprites[(*iter)].height = (BLOCK_SIZE * HEIGHT) / draw->sprites[(*iter)].dist;
	draw->sprites[(*iter)].tex_x = (int)draw->x % BLOCK_SIZE;
	draw->sprites[(*iter)].sprite_tex = cube()->map->sprites[i].sprite_tex;
	draw->sprites[(*iter)].frames = cube()->map->sprites[i].frames;
	draw->is_sprite = true;
	(*iter)++;
}

bool	find_hitbox(t_draw *draw, t_cube *c, int *iter)
{
	int i = 0;
	if (is_touching(draw->x, draw->y, c))
		return (true);
	if (touch_block(c->map->blocks, draw->x, draw->y))
		return (true);
	if (touch_block(c->map->doors, draw->x, draw->y))
		return (true);
	if (touch_line(c->map->lines, draw->x, draw->y))
		return (true);
	if ((i = touch_sprite(c->map->sprites, draw->x, draw->y)))
		get_sprite_coordinates(draw, i - 1, iter);
	return false;
}



bool	check_block_and_door(t_draw *draw, int sx, int sy,
		t_thread_params *params)
{
	if (touch_block(params->cube->map->doors, draw->x, draw->y))
	{
		if (touch_block(params->cube->map->doors, draw->x - sx, draw->y))
			draw->tex_x = (int)draw->x % BLOCK_SIZE;
		else
			draw->tex_x = (int)draw->y % BLOCK_SIZE;
		draw->texture = params->textures->door;
		return (true);
	}
	if (touch_block(params->cube->map->blocks, draw->x, draw->y))
	{
		if (touch_block(params->cube->map->blocks, draw->x - sx, draw->y))
			draw->tex_x = (int)draw->x % BLOCK_SIZE;
		else
			draw->tex_x = (int)draw->y % BLOCK_SIZE;
		draw->texture = params->textures->wall_west[params->player->level];
		return (true);
	}
	return (false);
}

void	direction(t_draw *draw, t_thread_params *params)
{
	int	sx;
	int	sy;

	sx = -1;
	sy = -1;
	if (draw->cosangle > 0)
		sx = 1;
	if (draw->sinangle > 0)
		sy = 1;
	if (check_block_and_door(draw, sx, sy, params))
		return ;
	if (is_touching(draw->x - sx, draw->y, params->cube))
	{
		draw->tex_x = (int)draw->x % BLOCK_SIZE;
		if (sy == 1)
			draw->texture = params->textures->wall_south[params->player->level];
		else
			draw->texture = params->textures->wall_north[params->player->level];
	}
	else if (is_touching(draw->x, draw->y - sy, params->cube))
	{
		draw->tex_x = (int)draw->y % BLOCK_SIZE;
		if (sx == 1)
			draw->texture = params->textures->wall_east[params->player->level];
		else
			draw->texture = params->textures->wall_west[params->player->level];
	}
}
