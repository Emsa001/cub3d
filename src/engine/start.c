/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/06/20 20:46:55 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_background() {

    t_texture *sky = textures()->sky;

    for (int y = 0; y < sky->height; y++) {
        for (int x = 0; x < sky->width; x++) {
            int pixel = *(int *)(sky->img_data + ((x + y * sky->width) * sky->bpp / 8));
            put_pixel(x, y, pixel);
        }
    }

    t_texture *floor = textures()->floor;

    for (int y = 0; y < floor->height; y++) {
        for (int x = 0; x < floor->width; x++) {
            int pixel = *(int *)(floor->img_data + ((x + y * floor->width) * floor->bpp / 8));
            put_pixel(x, y + HEIGHT / 1.62, pixel);
        }
    }
}

void render_view()
{
	t_cube *c = cube();

	float angle = player()->angle;
	int numRays = 200;
	int i = 0;

	float fovInRadians = player()->fov * PI / 180;
	float halfFovInRadians = fovInRadians / 2.0;
	float angleOffset = angle - halfFovInRadians;

	float rayWidth = (float)WIDTH / numRays; 

	while (i < numRays) {
		float fraction = (float)i / numRays;
		float rayAngle = angleOffset + fraction * fovInRadians;
		draw_line(rayAngle);
		c->x = rayWidth * i;
		i++;
	}
}

void render_map() {
    t_cube *c = cube();
    int i, j;

    for (i = 0; i < c->map->height; i++) {
        for (j = 0; j < c->map->width; j++) {
            if (c->map->map[i][j] == '1')
                draw_cube(j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, 0x00FF0000);
        }
    }
}

int render_scene(t_cube *c) {
    usleep(16666);
    render()->img_ptr = mlx_new_image(render()->mlx, WIDTH, HEIGHT);

    // render_background();
	render_view();

    mlx_put_image_to_window(render()->mlx, render()->win, render()->img_ptr, 0, 0);
    mlx_destroy_image(render()->mlx, render()->img_ptr);
    
    // render_map();
    move_player();
    draw_middle_line();
    return 0;
}

void start_game(void) {
    t_cube *c = cube();
    // print_map_info();
    c->win = mlx_new_window(c->mlx, WIDTH, HEIGHT, "Cub3D");
	render()->win = c->win;
    init_hooks();
}
