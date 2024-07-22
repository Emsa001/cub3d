/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:16:56 by escura            #+#    #+#             */
/*   Updated: 2024/07/22 18:57:45 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void cover(void){
    
}

void minimap_render(void)
{
    const t_cube *c = cube();
    const t_player *p = player();
    const t_minimap *m = minimap();

    // Minimap center
    float center_x = m->x + MINIMAP_PIXEL_WIDTH / 2.0f;
    float center_y = m->y + MINIMAP_PIXEL_HEIGHT / 2.0f;

    draw_circle(center_x, center_y, m->radius, MINIMAP_COLOR);

    // Calculate block rendering bounds
    float start_x = p->x - MINIMAP_RADIUS / (float)MINIMAP_BLOCK_SIZE;
    float start_y = p->y - MINIMAP_RADIUS / (float)MINIMAP_BLOCK_SIZE;
    float end_x = start_x + MINIMAP_RADIUS * 2 / (float)MINIMAP_BLOCK_SIZE;
    float end_y = start_y + MINIMAP_RADIUS * 2 / (float)MINIMAP_BLOCK_SIZE;

    int i = (int)start_y;
    while (i < (int)end_y)
    {
        int j = (int)start_x;
        while (j < (int)end_x)
        {
            if (i >= 0 && i < c->map->height && j >= 0 && j < c->map->width)
            {
                if (c->map->map[i][j] == '1')
                {
                    int screen_x = m->x + (int)((j - start_x) * MINIMAP_BLOCK_SIZE);
                    int screen_y = m->y + (int)((i - start_y) * MINIMAP_BLOCK_SIZE);

                    // Adjust to center the block
                    screen_x -= MINIMAP_BLOCK_SIZE * 2.05;
                    screen_y -= MINIMAP_BLOCK_SIZE * 2.05;

                    minimap_block(j, i, screen_x, screen_y);
                }
            }
            j++;
        }
        i++;
    }

    minimap_draw_player();
}