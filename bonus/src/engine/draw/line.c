/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:46:18 by escura            #+#    #+#             */
/*   Updated: 2024/09/08 19:50:30 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int direction(float x, float y, float cosangle, float sinangle, t_cube *c, int *tex_x)
{
    int sx = cosangle > 0 ? 1 : -1; 
    int sy = sinangle > 0 ? 1 : -1;

    if (is_touching(x - sx, y, c) || is_touching(x - sx, y - sy, c)) {
        *tex_x = (int)x % BLOCK_SIZE;
        return (sy == 1) ? 1 : 3;
    } else if (is_touching(x, y - sy, c) || is_touching(x, y, c)) {
        *tex_x = (int)y % BLOCK_SIZE;
        return (sx == 1) ? 2 : 4;
    } else if (touch_block(c->map->doors, x - sx, y)) {
        *tex_x = (int)x % BLOCK_SIZE;
        return 5;
    } else if (touch_block(c->map->doors, x, y - sy)) {
        *tex_x = (int)y % BLOCK_SIZE;
        return 5;
    } else if (touch_block(c->map->blocks, x - sx, y)) {
        *tex_x = (int)x % BLOCK_SIZE;
        return 6;
    } else if (touch_block(c->map->blocks, x, y)) {
        *tex_x = (int)y % BLOCK_SIZE;
        return 6;
    } else if (touch_line(c->map->lines, x - sx, y) == 1){
        *tex_x = (int)x % BLOCK_SIZE;
        return 3;
    } else if (touch_line(c->map->lines, x, y) == 1) {
        *tex_x = (int)y % BLOCK_SIZE;
        return 3;
    } else if(touch_line(c->map->lines, x - sx, y) == 2)
    {
        *tex_x = (int)x % BLOCK_SIZE;
        return 1;
    } else if(touch_line(c->map->lines, x, y) == 2)
    {
        *tex_x = (int)y % BLOCK_SIZE;
        return 1;
    }
    return 0;
}

int chest_direction(t_draw *draw, float cosangle, float sinangle, t_cube *c)
{
    int sx = 0;
    int sy = 0;
    if (cosangle > 0)
        sx = 1;
    else
        sx = -1;
    if (sinangle > 0)
        sy = 1;
    else
        sy = -1;
    if(touch_chest(c->map->chests, draw->first_x - sx, draw->first_y))
    {
        draw->tex_x = (int)draw->first_x % BLOCK_SIZE;
        return 7;
    } else if(touch_chest(c->map->chests, draw->first_x, draw->first_y))
    {
        draw->tex_x = (int)draw->first_y % BLOCK_SIZE;
        return 7;
    }
    return 0;
}

int torch_direction(t_draw *draw, float cosangle, float sinangle, t_cube *c)
{
    int sx = 0;
    int sy = 0;
    if (cosangle > 0)
        sx = 1;
    else
        sx = -1;
    if (sinangle > 0)
        sy = 1;
    else
        sy = -1;
    if(touch_torch(c->map->torches, draw->torch_x - sx, draw->torch_y))
    {
        draw->tex_x = (int)draw->torch_x % BLOCK_SIZE;
        return 9;
    } else if(touch_torch(c->map->torches, draw->torch_x, draw->torch_y))
    {
        draw->tex_x = (int)draw->torch_y % BLOCK_SIZE;
        return 9;
    }
    return 0;
}

static bool find_hitbox(float x, float y, t_cube *c)
{
    if (is_touching(x, y, c))
        return true;
    if (touch_block(c->map->blocks, x, y))
        return true;
    if (touch_block(c->map->doors, x, y))
        return true;
    if(touch_line(c->map->lines, x, y))
        return true;
    return false;
}

t_draw init_draw(void)
{
    t_draw draw;

    draw.x = player()->x_px;
    draw.y = player()->y_px;
    draw.first_x = 0;
    draw.first_y = 0;
    draw.last_x = 0;
    draw.last_y = 0;
    draw.wall_height = 0;
    draw.height = 0;
    draw.height_top = 0;
    draw.start_x = 0;
    draw.start_y = 0;
    draw.side = 0;
    draw.tex_x = 0;
    draw.angle = 0;
    draw.dist = 0;
    draw.chest_dist = 0;
    draw.torch_x = 0;
    draw.torch_y = 0;
    draw.torch_height = 0;
    return draw;
}

void draw_torch_frame(t_draw draw, ThreadParams *params)
{
    int color = params->color;
    float tex_y = 0;
    float step = (float)T_SIZE / draw.torch_height;
    const t_player *p = params->player;
    const t_render *r = params->render;

    int start_y = (p->z - 1) * draw.torch_height + vert_offset(p);
    int end_y = start_y + draw.torch_height;

    if(end_y > HEIGHT)
        end_y = HEIGHT;

    while (start_y < end_y)
    {
        color = get_pixel_from_image(params->textures->torch[0], draw.tex_x , tex_y);
        if(color > 0)
            put_pixel(draw.start_x, start_y, color, r);

        tex_y += step;
        start_y++;
    }
}

void draw_line(t_draw draw, ThreadParams *params)
{
    t_cube *c = params->cube;
    const t_player *p = params->player;

    float cosangle = cos(draw.angle);
    float sinangle = sin(draw.angle);
    
    bool save = false;
    bool save_last = false;

    while (!find_hitbox(draw.x, draw.y, c))
    {
        if(touch_torch(c->map->torches, draw.x, draw.y))
        {
            draw.torch_x = draw.x;
            draw.torch_y = draw.y;
        }
        if(touch_chest(c->map->chests, draw.x, draw.y))
        {
            if(!save)
            {
                save = true;
                draw.first_x = draw.x;
                draw.first_y = draw.y;
            }
            draw.x += cosangle;
            draw.y += sinangle;
            if(!save_last && !touch_chest(c->map->chests, draw.x, draw.y))
            {
                save_last = true;
                draw.last_x = draw.x;
                draw.last_y = draw.y;
            }
        }
        else
        {
            draw.x += cosangle;
            draw.y += sinangle;
        }
    }

    draw.side = direction(draw.x, draw.y, cosangle, sinangle, c, &draw.tex_x);
    lane_distance(&draw);
    draw_wall(draw, params);
    draw_floor(draw.wall_height, draw.start_x, params, draw.angle);
    draw_sky(draw.wall_height, draw.start_x, params, draw.angle);
    if(torch_direction(&draw, cosangle, sinangle, c) == 9)
        draw_torch_frame(draw, params);
    if(chest_direction(&draw, cosangle, sinangle, c) == 7)
    {   
        draw_chest_top(draw, params, draw.angle);
        draw_chest(draw, params, draw.tex_x, draw.angle);
    }
}
