/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/07/14 13:44:22 by btvildia         ###   ########.fr       */
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


// void render_map() {
//     t_cube *c = cube();
//     int i, j;

//     for (i = 0; i < c->map->height; i++) {
//         for (j = 0; j < c->map->width; j++) {
//             if (c->map->map[i][j] == '1')
//                 draw_cube(j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, 0x00FF0000);
//         }
//     }
// }

void update_fps(t_cube *c) 
{
    time_t current_time = time(NULL);
    c->frame_count++;

    if (current_time - c->last_time >= 1) {
        c->fps = c->frame_count;
        c->frame_count = 0;
        c->last_time = current_time;
    }

    char fps_str[50];
    sprintf(fps_str, "(fps: %d)", c->fps);
    mlx_string_put(c->mlx, c->win, 10, 10, 0xFFFFFF, fps_str);
}

int render_scene(t_cube *c) {
    // usleep(16666);
    render()->img_ptr = mlx_new_image(render()->mlx, WIDTH, HEIGHT);

    // render_background();
	render_view();
    // for(int i = 0; i < 500; i++){
    //     draw_h_line(500, i);
    // }


    mlx_put_image_to_window(render()->mlx, render()->win, render()->img_ptr, 0, 0);
    mlx_destroy_image(render()->mlx, render()->img_ptr);
    
    // render_map();
    move_player();
    draw_cross_in_centre();
    update_fps(c);
    return 0;
}

void start_game(void) {
    t_cube *c = cube();
    // print_map_info();
    c->win = mlx_new_window(c->mlx, WIDTH, HEIGHT, "Cub3D");
	render()->win = c->win;
    init_hooks();
}


// void	draw_cube(int x, int y, int size, int col)
// {
// 	int				i;
// 	const t_cube	*c = cube();

// 	i = 0;
// 	while (i < size)
// 	{
// 		mlx_pixel_put(c->mlx, c->win, x + i - size / 2, y - size / 2, col);
// 		mlx_pixel_put(c->mlx, c->win, x - size / 2, y + i - size / 2, col);
// 		mlx_pixel_put(c->mlx, c->win, x + i - size / 2, y + size / 2, col);
// 		mlx_pixel_put(c->mlx, c->win, x + size / 2, y + i - size / 2, col);
// 		i++;
// 	}
// }