/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:16:56 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 20:08:50 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MINIMAP_BLOCK_SIZE 48

#define MINIMAP_PIXEL_WIDTH 400
#define MINIMAP_PIXEL_HEIGHT 400

#define MINIMAP_RADIUS 300 
#define MINIMAP_RATIO 1.6 

#define PLAYER_SIZE 20

void put_map_block(int x, int y, int screen_x, int screen_y, float center_x, float center_y, int radius)
{
    const t_texture *src_texture = textures()->wall_north;
    static t_texture dst_texture = {0};

    // Initialize the destination texture only once
    if (!dst_texture.data)
    {
        dst_texture.width = MINIMAP_BLOCK_SIZE;
        dst_texture.height = MINIMAP_BLOCK_SIZE;
        dst_texture.bpp = src_texture->bpp;
        dst_texture.size_line = dst_texture.width * (dst_texture.bpp / 8);
        dst_texture.endian = src_texture->endian;
        dst_texture.data = (char *)ft_malloc(dst_texture.size_line * dst_texture.height);

        // Resize the texture once
        resize_texture(src_texture, &dst_texture, MINIMAP_BLOCK_SIZE, MINIMAP_BLOCK_SIZE);
    }

    for (int j = 0; j < dst_texture.height; j++)
    {
        for (int i = 0; i < dst_texture.width; i++)
        {
            int color = get_pixel_from_image(&dst_texture, i, j);
            
            float pixel_x = screen_x + i;
            float pixel_y = screen_y + j;

            float dx = pixel_x - center_x;
            float dy = pixel_y - center_y;
            if (dx * dx + dy * dy <= radius * radius)
            {
                put_pixel((int)pixel_x, (int)pixel_y, color);
            }
        }
    }
}

void draw_circle(int center_x, int center_y, int radius)
{
    int x = radius + 2;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        // Fill the circle by drawing horizontal lines
        for (int i = center_x - x; i <= center_x + x; i++)
        {
            put_pixel(i, center_y + y, 0x27272a);
            put_pixel(i, center_y - y, 0x27272a);
        }

        for (int i = center_x - y; i <= center_x + y; i++)
        {
            put_pixel(i, center_y + x, 0x27272a);
            put_pixel(i, center_y - x, 0x27272a);
        }

        y++;
        err += 2 * y + 1;

        if (err > x * 2)
        {
            x--;
            err -= 2 * x + 1;
        }
    }
}

bool is_wall(float x, float y)
{
    const t_cube *c = cube();

    printf("map_x: %f, map_y: %f\n", x,y);

    return false;
}

void draw_fov(float x, float y, float angle)
{
    int col = 0;
    for (int i = 0; i < 100; i++)
    {
        if(col > 20)
            break;
        x += cos(angle);
        y += sin(angle);
        if(get_scene_pixel((int)x, (int)y) == 2565930){
            put_pixel((int)x, (int)y, 0xa1a1aa);
        }else
            col++;
    }
}

void draw_player(float x, float y) {
    const t_player *p = player();
    const t_render *r = render();

    float angle = player()->angle;
    int i = 0;

    float fovInRadians = player()->fov * PI / 180;
    float halfFovInRadians = fovInRadians / 2.0;
    float angleOffset = angle - halfFovInRadians;

    while (i < WIDTH)
    {
        float fraction = (float)i / WIDTH;
        float rayAngle = angleOffset + fraction * fovInRadians;
        draw_fov(x, y, rayAngle);
        i += 170 - player()->fov;
    }
}

void render_minimap(void)
{
    const t_cube *c = cube();
    const t_player *p = player();

    // Minimap position
    int minimap_top_left_x = WIDTH - MINIMAP_PIXEL_WIDTH;
    int minimap_top_left_y = 0;

    // Minimap center
    float center_x = minimap_top_left_x + MINIMAP_PIXEL_WIDTH / 2.0f;
    float center_y = minimap_top_left_y + MINIMAP_PIXEL_HEIGHT / 2.0f;

    draw_circle(center_x, center_y, MINIMAP_RADIUS / MINIMAP_RATIO);

    // Calculate block rendering bounds
    float start_x = p->x - MINIMAP_RADIUS / (float)MINIMAP_BLOCK_SIZE;
    float start_y = p->y - MINIMAP_RADIUS / (float)MINIMAP_BLOCK_SIZE;
    float end_x = start_x + MINIMAP_RADIUS * 2 / (float)MINIMAP_BLOCK_SIZE;
    float end_y = start_y + MINIMAP_RADIUS * 2 / (float)MINIMAP_BLOCK_SIZE;


    for (int i = (int)start_y; i < (int)end_y; i++)
    {
        for (int j = (int)start_x; j < (int)end_x; j++)
        {
            if (i >= 0 && i < c->map->height && j >= 0 && j < c->map->width)
            {
                if (c->map->map[i][j] == '1')
                {
                    int screen_x = minimap_top_left_x + (int)((j - start_x) * MINIMAP_BLOCK_SIZE);
                    int screen_y = minimap_top_left_y + (int)((i - start_y) * MINIMAP_BLOCK_SIZE);

                    // Adjust to center the block
                    screen_x -= MINIMAP_BLOCK_SIZE * 2.05;
                    screen_y -= MINIMAP_BLOCK_SIZE * 2.05;

                    put_map_block(j, i, screen_x, screen_y, center_x, center_y, MINIMAP_RADIUS / MINIMAP_RATIO);
                }
            }
        }
    }

    draw_player(center_x, center_y);
}
