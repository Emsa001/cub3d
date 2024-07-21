/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:16:13 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 15:36:13 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_floor_ceeling()
{
    const t_cube *c = cube();
    const int floor = (c->map->f[0] << 16 | c->map->f[1] << 8 | c->map->f[2]);
    const int ceeling = (c->map->c[0] << 16 | c->map->c[1] << 8 | c->map->c[2]);

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
    render_floor_ceeling();
    
	render_view();
    mlx_put_image_to_window(r->mlx, r->win, r->img_ptr , 0, 0);
    mlx_destroy_image(r->mlx, r->img_ptr);

    move_player();

    return 0;
}

void start_game(void) 
{
    t_cube *c = cube();
    c->win = mlx_new_window(c->mlx, WIDTH, HEIGHT, "Cub3D");
	render()->win = c->win;
    init_hooks();
}
