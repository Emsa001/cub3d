/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:03:04 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 16:14:40 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int vert_offset(t_player *p)
{
    return (p->z_dir) * HEIGHT;
}

static t_texture *get_wall_side(int side, const t_textures *texs)
{
    t_texture *t = NULL;
    if (side == 1)
        t = texs->wall_north;
    else if (side == 2)
        t = texs->wall_south;
    else if (side == 3)
        t = texs->wall_east;
    else if (side == 4)
        t = texs->wall_west;
    else if (side == 5)
        t = texs->door;
    else if (side == 6)
        t = texs->wall_west;
    return t;
}

void draw_wall(float height, int start_x, ThreadParams *params) {

    const t_cube *c = params->cube;
    const t_player *p = params->player;
    const t_render *r = params->render;
    const t_textures *texs = params->textures;

    int color = 0;
    float tex_y = 0;
    int start_y = 0;
    int end = 0;
    float step = T_SIZE / height;

    if (height > HEIGHT) {
        tex_y = ((height - HEIGHT) * step / 2);
        height = HEIGHT;
    }

    if (r->side != 6) {
    	start_y = (p->z * height + vert_offset(p));
    } else {
        start_y = ((p->z - c->map->blocks[0].z) * height + vert_offset(p));
    }
    end = start_y + height;

    t_texture *wall_side = get_wall_side(r->side, texs);
    while (start_y < end) {
        if (p->catch && r->side == 6)
            color = 255;
        else
            color = get_pixel_from_image(wall_side, c->tex_x, tex_y);
        put_pixel(start_x, start_y, color, params->render);
        tex_y += step;
        start_y++;
    }
}
