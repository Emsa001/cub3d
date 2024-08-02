/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/08/02 20:44:44 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_background() {

    t_texture *sky = textures()->sky;

    for (int y = 0; y < sky->height; y++) {
        for (int x = 0; x < sky->width; x++) {
            int pixel = *(int *)(sky->data + ((x + y * sky->width) * sky->bpp / 8));
            put_pixel(x, y, pixel);
        }
    }

    t_texture *floor = textures()->floor;

    for (int y = 0; y < floor->height; y++) {
        for (int x = 0; x < floor->width; x++) {
            int pixel = *(int *)(floor->data + ((x + y * floor->width) * floor->bpp / 8));
            put_pixel(x, y + HEIGHT / 1.62, pixel);
        }
    }
}

void update_fps(void) 
{
    static int fps = 0;
    static int last_fps = 0;
    static time_t last_time = 0;
    const t_render *r = render();
    
    time_t now = time(NULL);
    fps++;
    if (now - last_time >= 1) 
    {
        last_time = now;
        last_fps = fps;
        fps = 0;
    }
    
    char *fps_str = ft_itoa(last_fps);
    mlx_string_put(r->mlx, r->win, 10, 10, 0xFFFFFF, fps_str);
    ft_free(fps_str);
}

int render_scene(t_cube *c) 
{
    t_render *r = render();
    r->img_ptr = mlx_new_image(r->mlx, WIDTH, HEIGHT);

    // render_background();
	render_view();
    minimap_render();
    
    mlx_put_image_to_window(r->mlx, r->win, r->img_ptr , 0, 0);
    mlx_destroy_image(r->mlx, r->img_ptr);
    
    move_player();
    draw_cross_in_centre();
    update_fps();
    return 0;
}

void start_game(void) {
    // start the game
    init_hooks();
}

