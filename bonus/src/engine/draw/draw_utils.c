/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:25:20 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/03 20:07:12 by escura           ###   ########.fr       */
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

float	get_check(int *start_y, int *end_y, float *step, float height)
{
	float	tex_y;

	tex_y = 0;
	(*step) = ((float)T_SIZE) / height;
	(*start_y) = (player()->z - 1) * height + HEIGHT / 2;
	(*end_y) = (*start_y) + height;
	if ((*start_y) < 0)
	{
		tex_y = -(*start_y) * (*step);
		(*start_y) = 0;
	}
	if ((*end_y) > HEIGHT)
		(*end_y) = HEIGHT;
	return (tex_y);
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

static bool	check_block_and_door(t_draw *draw, int sx,
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
	if (check_block_and_door(draw, sx, params))
		return ;
	if (is_touching(draw->x - sx, draw->y, params->cube))
	{
		draw->tex_x = (int)draw->x % BLOCK_SIZE;
		draw->texture = params->textures->wall_north[params->player->level];
		if (sy == 1)
			draw->texture = params->textures->wall_south[params->player->level];
	}
	else if (is_touching(draw->x, draw->y - sy, params->cube))
	{
		draw->tex_x = (int)draw->y % BLOCK_SIZE;
		draw->texture = params->textures->wall_west[params->player->level];
		if (sx == 1)
			draw->texture = params->textures->wall_east[params->player->level];
	}
}
