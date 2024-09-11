/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:46:18 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 14:46:22 by escura           ###   ########.fr       */
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

int sprite_direction(t_draw *draw, float cosangle, float sinangle, t_cube *c)
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
    if(touch_sprite(c->map->sprites, draw->sprite_x - sx, draw->sprite_y))
    {
        draw->tex_x = (int)draw->sprite_x % BLOCK_SIZE;
        return 9;
    } else if(touch_sprite(c->map->sprites, draw->sprite_x, draw->sprite_y))
    {
        draw->tex_x = (int)draw->sprite_y % BLOCK_SIZE;
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
    draw.sprite_x = 0;
    draw.sprite_y = 0;
    draw.sprite_height = 0;
    return draw;
}

long current_frame(int frames)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long curr_time =  (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    int curr_frame = (curr_time / 100) % frames;
    return curr_frame;
}


void sprite_frame(t_draw draw, ThreadParams *params, t_sprite sprite)
{
    int color = params->color;
    float tex_y = 0;
    float step = (float)T_SIZE / draw.sprite_height;
    const t_player *p = params->player;
    const t_render *r = params->render;
    int dist = draw.sprite_dist;
    const t_textures *texs = params->textures;

    int start_y = (p->z - 1) * draw.sprite_height + vert_offset(p);
    int end_y = start_y + draw.sprite_height;

    t_texture *sprite_tex = sprite.sprite_tex[current_frame(sprite.frames)];

    if(end_y > HEIGHT)
        end_y = HEIGHT;

    while (start_y < end_y)
    {
        if(!p->vision && dist > 450)
            break;
        color = get_pixel_from_image(sprite_tex, draw.tex_x , tex_y);
        if(!p->vision)
            color = darken_color(color, (float)dist / 450);
        if(color != 0)
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
    int i = 0;
    int j = 1;

    while (!find_hitbox(draw.x, draw.y, c))
    {
        if((i = touch_sprite(c->map->sprites, draw.x, draw.y)))
        {
            draw.sprite_x = draw.x;
            draw.sprite_y = draw.y;
            if(i > 1)
                j = i;
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

    if(sprite_direction(&draw, cosangle, sinangle, c) == 9)
        sprite_frame(draw, params, c->map->sprites[j - 1]);
    if(chest_direction(&draw, cosangle, sinangle, c) == 7)
    {   
        draw_chest_top(draw, params, draw.angle);
        draw_chest(draw, params, draw.tex_x, draw.angle);
    }
}
