/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:49:03 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 14:41:46 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool is_portal(t_sprite *sprites, int i)
{
    if(sprites[i].type == 'P')
        return true;
    return false;
}

bool touch_closed_portal(t_sprite *sprites, float px, float py)
{

	int i = 0;
	float x, y;
	
	if (!sprites)
		return false;

	while (sprites[i].x != -1)
	{
        x = sprites[i].x * BLOCK_SIZE;
        y = sprites[i].y * BLOCK_SIZE;

        
        if (px >= x && px <= x + sprites[i].width && py >= y && py <= y)
        {
            if(is_portal(sprites, i))
                return true;
        }
		i++;
	}

	return false;
}

void check_level(t_point *portals, int px, int py)
{
    int i = 0;
    float x = 0;
    float y = 0;

    if(!portals)
        return;

    while (portals[i].x != -1)
    {
        x = portals[i].x * BLOCK_SIZE;
        y = portals[i].y * BLOCK_SIZE;
        {
            if(py < portals[i].y * BLOCK_SIZE + 10)
            {
                player()->level = 2 - i;
                break;
            }
            else
                player()->level = 0;
        }
        i++;
    }
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
            check_level(c->map->portals, x, y);
            if (is_touching(x, y, c) || 
                touch_block(c->map->blocks, x, y) || 
                touch_block(c->map->doors, x, y) ||
                touch_generator(c->map->generators, x, y) ||
                touch_line(c->map->lines, x, y) || 
                touch_closed_portal(c->map->sprites, x, y))
                return true;
            y++;
        }
        x++;
    }
    return false;
}