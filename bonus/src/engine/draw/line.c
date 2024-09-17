/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:46:18 by escura            #+#    #+#             */
/*   Updated: 2024/09/17 18:02:17 by btvildia         ###   ########.fr       */
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
    } else if (touch_line(c->map->lines, x, y) == 1){
        *tex_x = (int)x % BLOCK_SIZE;
        return 3;
    } else if(touch_line(c->map->lines, x, y) == 2)
    {
        *tex_x = (int)y % BLOCK_SIZE;
        return 1;
    }
    return 0;
}

int generator_direction(t_draw *draw, float cosangle, float sinangle, t_cube *c)
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
    if(touch_generator(c->map->generators, draw->first_x - sx, draw->first_y))
    {
        draw->tex_x = (int)draw->first_x % BLOCK_SIZE;
        return 7;
    } else if(touch_generator(c->map->generators, draw->first_x, draw->first_y))
    {
        draw->tex_x = (int)draw->first_y % BLOCK_SIZE;
        return 7;
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
    draw.generator_dist = 0;
    draw.sprite_x = 0;
    draw.sprite_y = 0;
    draw.sprite_height = 0;
    draw.sprite_dist = 0;
    draw.facing_sprite_x = 0;
    draw.facing_sprite_y = 0;
    draw.facing_sprite_height = 0;
    draw.facing_sprite_dist = 0;
    return draw;
}

long current_frame(int frames)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int time_delay = 1000 / frames;
    if(frames == 28)
        time_delay = 90;
    if(frames == 5)
        time_delay = 60;
    if(frames == 2)
        time_delay = 150;
    long curr_time =  (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    int curr_frame = (curr_time / time_delay) % frames;

    return curr_frame;
}

void put_line(t_draw draw, ThreadParams *params)
{
    int start = 0;
    int end = HEIGHT;
    int i = 0;
    while (start < end)
    {
        put_pixel(draw.start_x, start, draw.colors[start], params->render);
        start++;
    }
}



int touch_sprite(t_sprite *sprites, float px, float py)
{
    int i = 0;
    float x = 0;
    float y = 0;
    
    if (!sprites)
        return 0;

    while (sprites[i].x != -1)
    {
        x = sprites[i].x * BLOCK_SIZE;
        y = sprites[i].y * BLOCK_SIZE;

        if (px >= x && px <= x + sprites[i].width && py >= y && py <= y + 1)
            return i + 1;
        i++;
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
    } else if(touch_sprite(c->map->sprites, draw->sprite_x, draw->sprite_y - sy))
    {
        draw->tex_x = (int)draw->sprite_y % BLOCK_SIZE;
        return 9;
    }
    return 0;
}

bool touch_facing_sprite(t_draw *draw, t_sprite *sprites, float px, float py);

// int facing_sprite_direction(t_draw *draw, float cosangle, float sinangle, t_cube *c)
// {
//     int sx = 0;
//     int sy = 0;
//     if (cosangle > 0)
//         sx = 1;
//     else
//         sx = -1;
//     if (sinangle > 0)
//         sy = 1;
//     else
//         sy = -1;
    
//     if(touch_facing_sprite(c->map->facing, draw->facing_sprite_x, draw->facing_sprite_y))
//     {
//         draw->tex_x = (int)draw->facing_sprite_y % BLOCK_SIZE;
//         return 10;
//     }
//     return 0;
// }

void sprite_frame(t_draw draw, ThreadParams *params, t_sprite sprite)
{
    int color = params->color;
    float tex_y = 0;
    float step = ((float)T_SIZE) / draw.sprite_height;
    const t_player *p = params->player;
    t_render *r = params->render;
    int dist = draw.sprite_dist;
    const t_textures *texs = params->textures;

    int start_y = (p->z - 1) * draw.sprite_height + vert_offset(p);
    int end_y = start_y + draw.sprite_height;


    t_texture *sprite_tex = sprite.sprite_tex[current_frame(sprite.frames)];

    if(end_y > HEIGHT)
        end_y = HEIGHT;
    if(start_y < 0)
    {
        tex_y = -start_y * step;
        start_y = 0;
    }

    while (start_y < end_y)
    {
        color = get_pixel_from_image(sprite_tex, (draw.tex_x) , tex_y);
        color = darken_color(color, (float)dist / 450);

        if(color && color > 0)
            put_pixel(draw.start_x, start_y, color, r);

        tex_y += step;
        start_y++;
    }
}

void facing_sprite_frame(t_draw draw, ThreadParams *params, t_sprite sprite)
{
    int color = params->color;
    float tex_y = 0;
    float step = ((float)T_SIZE ) / draw.facing_sprite_height;
    const t_player *p = params->player;
    t_render *r = params->render;
    int dist = draw.facing_sprite_dist;
    const t_textures *texs = params->textures;

    int start_y = (p->z - 1) * draw.facing_sprite_height + vert_offset(p);
    int end_y = start_y + draw.facing_sprite_height;

    t_texture *sprite_tex = sprite.sprite_tex[current_frame(sprite.frames)];

    if(end_y > HEIGHT)
        end_y = HEIGHT;
    if(start_y < 0)
    {
        tex_y = -start_y * step;
        start_y = 0;
    }

    while (start_y < end_y)
    {
        color = get_pixel_from_image(sprite_tex, (draw.tex_x) , tex_y);

        if(color && color > 0)
            put_pixel(draw.start_x, start_y, color, r);

        tex_y += step;
        start_y++;
    }
}

bool touch_facing(t_draw *draw, float px, float py , float sprite_x, float sprite_y, int width)
{
    // it's the same as cos(angle + 90)
    float cosangle = cos(player()->angle);
    // it's the same as sin(angle + 90)
    float sinangle = sin(player()->angle);

 
    float u = (cosangle * (sprite_x - px) + sinangle * (sprite_y - py));
    if (u < 0 || u > 2)
        return false;
    float v = (-sinangle * (sprite_x - px) + cosangle * (sprite_y - py));
    draw->tex_x = (int)v + width / 2;
    float dist = distance(px, py, sprite_x, sprite_y);
    if (dist * 2 < width)
        return true;
    return false;
}

bool touch_facing_sprite(t_draw *draw, t_sprite *sprites, float px, float py)
{
    int i = 0;
    float x = 0;
    float y = 0;
    
    if (!sprites)
        return false;

    while (sprites[i].x != -1)
    {
        x = sprites[i].x * BLOCK_SIZE;
        y = sprites[i].y * BLOCK_SIZE;
        int width = sprites[i].width;
        if(touch_facing(draw,px, py, x, y, width))
            return true;
        i++;
    }

    return false;
}

void draw_line(t_draw draw, ThreadParams *params)
{   
    t_cube *c = params->cube;
    const t_player *p = params->player; 
    float cosangle = cos(draw.angle);
    float sinangle = sin(draw.angle);
    
    bool save = false;
    bool save_last = false;
    bool save_sprite = false;
    bool save_facing_sprite = false;
    

    while (!find_hitbox(draw.x, draw.y, c))
    {
        if(touch_sprite(c->map->sprites, draw.x, draw.y))
        {
            if(!save_sprite)
            {
                draw.sprite_x = draw.x;
                draw.sprite_y = draw.y;
            }
            save_sprite = true;
        }
        if(touch_facing_sprite(&draw,c->map->facing, draw.x, draw.y))
        {
            if(!save_facing_sprite)
            {
                draw.facing_sprite_x = draw.x;
                draw.facing_sprite_y = draw.y;
            }
            save_facing_sprite = true;
        }
        if(touch_generator(c->map->generators, draw.x, draw.y))
        {
            if(!save)
            {
                save = true;
                draw.first_x = draw.x;
                draw.first_y = draw.y;
            }
            draw.x += cosangle;
            draw.y += sinangle;
            if(!save_last && !touch_generator(c->map->generators, draw.x, draw.y))
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
    draw_scene(&draw, params);
    
    int scale = draw.start_x + WIDTH_SCALE;
    while(draw.start_x < scale)
    {
        put_line(draw, params);
        if(sprite_direction(&draw, cosangle, sinangle, c) == 9)
            sprite_frame(draw, params, c->map->sprites[0]);
        if(touch_facing_sprite(&draw,c->map->facing, draw.facing_sprite_x, draw.facing_sprite_y))
            facing_sprite_frame(draw, params, c->map->facing[0]);
        if(generator_direction(&draw, cosangle, sinangle, c) == 7)
        {   
            draw_generator_top(draw, params, draw.angle);
            draw_generator(draw, params, draw.tex_x, draw.angle);
        }
        draw.start_x++;
    }
}