/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:49:03 by escura            #+#    #+#             */
/*   Updated: 2024/09/07 16:53:01 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
                touch_chest(c->map->chests, x, y) ||
                touch_line(c->map->lines, x, y))
                return true;
            y++;
        }
        x++;
    }

    return false;
}