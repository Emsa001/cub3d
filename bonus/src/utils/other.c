/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:47:44 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 19:17:16 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_if_point_is_on_line(t_block line, float px, float py)
{
	t_vars	vars;
	float	x;
	float	y;
	float	dist;

	vars = (t_vars){0};
	vars.x = line.s_x * BLOCK_SIZE;
	vars.y = line.s_y * BLOCK_SIZE;
	vars.x1 = line.x * BLOCK_SIZE;
	vars.y1 = line.y * BLOCK_SIZE;
	vars.dx = vars.x2 - vars.x1;
	vars.dy = vars.y2 - vars.y1;
	vars.d = sqrt(vars.dx * vars.dx + vars.dy * vars.dy);
	vars.u = ((px - vars.x1) * vars.dx + (py - vars.y1) * vars.dy) / (vars.d
			* vars.d);
	if (vars.u < 0.0 || vars.u > 1.0)
		return (false);
	x = vars.x1 + vars.u * vars.dx;
	y = vars.y1 + vars.u * vars.dy;
	dist = sqrt((x - px) * (x - px) + (y - py) * (y - py));
	if (dist < (L_WIDTH / 2))
		return (true);
	return (false);
}

// float x1 = line.s_x * BLOCK_SIZE;
// float y1 = line.s_y * BLOCK_SIZE;
// float x2 = line.x * BLOCK_SIZE;
// float y2 = line.y * BLOCK_SIZE;
// float dx = x2 - x1;
// float dy = y2 - y1;
// float d = sqrt(dx * dx + dy * dy);
// float u = ((px - x1) * dx + (py - y1) * dy) / (d * d);

// if (u < 0.0 || u > 1.0)
//     return (false);

// float x = x1 + u * dx;
// float y = y1 + u * dy;
// float dist = sqrt((x - px) * (x - px) + (y - py) * (y - py));
// if (dist < (L_WIDTH / 2))
//     return (true);
// return (false);


int get_pixel_from_image(t_texture *t, int x, int y)
{
    if (t == NULL || t->data == NULL) {
        return 0;
    }

    x = x % t->width;
    y = y % t->height;

    if (x >= 0 && x < t->width && y >= 0 && y < t->height) {
        char *pixel = t->data + (y * t->size_line + x * (t->bpp / 8));
        return *(int *)pixel;
    }
    return 0;
}
