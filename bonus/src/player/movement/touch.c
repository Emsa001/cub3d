/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:49:03 by escura            #+#    #+#             */
/*   Updated: 2024/08/03 18:25:38 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch()
{
	const int	x = player()->x_px;
	const int	y = player()->y_px;
	const char	**map = cube()->map->map;

    const int x_p = x + 10;
    const int y_p = y + 10;
    const int x_m = x - 10;
    const int y_m = y - 10;
    t_cube *c = cube();

    if(is_touching(x_m , y_m,c) || is_touching(x_p , y_m,c) || is_touching(x_m , y_p,c) || is_touching(x_p , y_p,c))
        return (true);
    if(touch_block(c->map->blocks, x_m, y_m) || touch_block(c->map->blocks, x_p, y_m) || touch_block(c->map->blocks, x_m, y_p) || touch_block(c->map->blocks, x_p, y_p))
        return (true);
    if(touch_block(c->map->doors, x_m, y_m) || touch_block(c->map->doors, x_p, y_m) || touch_block(c->map->doors, x_m, y_p) || touch_block(c->map->doors, x_p, y_p))
        return (true);

	return (false);
}
