/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:30:33 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 14:50:03 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool touch_block(t_block *blocks, float px, float py)
{
	int i = 0;
	float x, y;

	if (!blocks)
		return false;

	while (blocks[i].x != -1)
	{
		x = blocks[i].x * BLOCK_SIZE;
		y = blocks[i].y * BLOCK_SIZE;
		if (px >= x && px <= x + BLOCK_SIZE && py >= y && py <= y + BLOCK_SIZE)
			return true;
		i++;
	}
	return false;
}

bool check_if_point_is_on_line(t_block line, float px, float py)
{
	float x1 = line.s_x * BLOCK_SIZE;
	float y1 = line.s_y * BLOCK_SIZE;
	float x2 = line.x * BLOCK_SIZE;
	float y2 = line.y * BLOCK_SIZE;
	float dx = x2 - x1;
	float dy = y2 - y1;
	float d = sqrt(dx * dx + dy * dy);
	float u = ((px - x1) * dx + (py - y1) * dy) / (d * d);

	if (u < 0.0 || u > 1.0)
		return false;

	float x = x1 + u * dx;
	float y = y1 + u * dy;
	float dist = sqrt((x - px) * (x - px) + (y - py) * (y - py));
	if (dist < (L_WIDTH / 2))
		return true;
	return false;
}

int touch_line(t_block *lines, float px, float py)
{
	int i = 0;
	float x, y;

	if (!lines)
		return false;
	
	while (lines[i].x != -1)
	{
		x = lines[i].x * BLOCK_SIZE - L_WIDTH;
		y = lines[i].y * BLOCK_SIZE - L_WIDTH;
		if (px >= x && px <= x + (L_WIDTH * 2) && py >= y && py <= y + (L_WIDTH * 2))
			return 2;
		x = lines[i].s_x * BLOCK_SIZE - L_WIDTH;
		y = lines[i].s_y * BLOCK_SIZE - L_WIDTH;
		if (px >= x && px <= x + (L_WIDTH * 2) && py >= y && py <= y + (L_WIDTH * 2))
			return 2;
		if(check_if_point_is_on_line(lines[i], px, py))
			return 1;
		i++;
	}
	
	return 0;
}

int touch_sprite(t_sprite *sprites, float px, float py)
{

	int i = 0;
	float x, y;
	
	if (!sprites)
		return false;

	while (sprites[i].x != -1)
	{
		x = sprites[i].x * BLOCK_SIZE;
		y = sprites[i].y * BLOCK_SIZE;

		if (px >= x && px <= x + sprites[i].width && py >= y && py <= y + 1)
			return i + 1;

		i++;
	}

	return false;
}


bool touch_generator(t_block *lines, float px, float py)
{
	int i = 0;
	float x, y;

	if (!lines)
		return false;
	
	while (lines[i].x != -1)
	{
		x = lines[i].x * BLOCK_SIZE;
		y = lines[i].y * BLOCK_SIZE;
		if (px >= x && px <= x + BLOCK_SIZE / 2 && py >= y && py <= y + BLOCK_SIZE / 2)
			return true;
		i++;
	}
	
	return false;
}

bool is_touching(float px, float py, const t_cube *c)
{
	int x = px / BLOCK_SIZE;
	int y = py / BLOCK_SIZE;

	if (x < 0 || y < 0 || x >= c->map->width || y >= c->map->height)
		return (true);
	if (c->map->map[y][x] == WALL)
		return (true);
	return (false);
}

void draw_middle_line(void)
{
	const t_cube *c = cube();
	int i;

	i = 0;
	while (i < WIDTH)
	{
		put_pixel(i, HEIGHT / 2, 0x00FF0000, render());
		i++;
	}
}

