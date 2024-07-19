/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/07/19 14:13:00 by btvildia         ###   ########.fr       */
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

void render_floor_ceeling()
{
    int floor;
    int ceeling;
    t_cube *c = cube();

    floor = (c->map->f[0] << 16 | c->map->f[1] << 8 | c->map->f[2]);
    ceeling = (c->map->c[0] << 16 | c->map->c[1] << 8 | c->map->c[2]);

    t_render *r = render();
    for (int y = 0; y < HEIGHT / 2; y++) {
        for (int x = 0; x < WIDTH; x++) {
            put_pixel(x, y, floor);
        }
    }
    for (int y = HEIGHT / 2; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            put_pixel(x, y, ceeling);
        }
    }
}

int render_scene(t_cube *c) 
{
    t_render *r = render();
    r->img_ptr = mlx_new_image(r->mlx, WIDTH, HEIGHT);
    // render_background();
    render_floor_ceeling();
    
	render_view();
    mlx_put_image_to_window(r->mlx, r->win, r->img_ptr , 0, 0);
    mlx_destroy_image(r->mlx, r->img_ptr);

    // draw_middle_line();
    move_player();

    return 0;
}

void start_game(void) 
{
    t_cube *c = cube();
    // print_map_info();
    c->win = mlx_new_window(c->mlx, WIDTH, HEIGHT, "Cub3D");
	render()->win = c->win;
    init_hooks();
}
