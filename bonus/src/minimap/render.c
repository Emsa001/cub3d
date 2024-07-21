/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:16:56 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 15:17:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_minimap() 
{
    t_cube *c = cube();
    int i, j;

    for (i = 0; i < c->map->height; i++) {
        for (j = 0; j < c->map->width; j++) {
            if (c->map->map[i][j] == '1')
                draw_cube(j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, 0x00FF0000);
        }
    }
}