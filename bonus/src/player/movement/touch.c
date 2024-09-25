/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:49:03 by escura            #+#    #+#             */
/*   Updated: 2024/09/25 15:11:33 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool touch_circle(float px, float py , float circle_x, float circle_y)
{
	int i = 0;
	float x = 0;
    float y = 0;

    x = circle_x * BLOCK_SIZE;
    y = circle_y * BLOCK_SIZE;
	float dist = sqrt(pow(px - x, 2) + pow(py - y, 2));
    if (dist <= 30)
        return true;
	return false;
}

bool check_level(t_point *portals, float px, float py)
{

	int i = 0;
	float x = 0;
    float y = 0;
    t_sprite *sprites = cube()->map->sprites;
	
	if (!portals)
		return false;

	while (portals[i].x != -1)
	{
        x = portals[i].x * BLOCK_SIZE;
        y = portals[i].y * BLOCK_SIZE;
        if (px >= x && px <= x + BLOCK_SIZE && py >= y && py <= y && sprites[i].type == 'P')
            return true;
        if(py < portals[i].y * BLOCK_SIZE + 10)
        {
            player()->level = (cube()->levels - 1) - i;
            break;
        }
        else
            player()->level = 0;
		i++;
	}
	return false;
}

bool touch()
{
    t_cube *c = cube();

    int x = player()->x_px - 10;
    int y = player()->y_px - 10;


    while (x <= player()->x_px + 10)
    {
        y = player()->y_px - 10;
        while (y <= player()->y_px + 10)
        {
            if (is_touching(x, y, c) || 
                touch_block(c->map->blocks, x, y) || 
                touch_block(c->map->doors, x, y) ||
                touch_generator(c->map->generators, x, y) ||
                touch_line(c->map->lines, x, y) ||
                check_level(c->map->portals, x, y))
                return true;
            y++;
        }
        x++;
    }
    return false;
}
