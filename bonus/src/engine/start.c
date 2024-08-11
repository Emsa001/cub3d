/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 15:41:41 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void draw_cube(int x, int y, int size, int col)
{
    int i;
    const t_cube *c = cube();

    i = 0;
    while (i < size)
    {
        mlx_pixel_put(c->mlx, c->win, x + i - size / 2, y - size / 2, col);
        mlx_pixel_put(c->mlx, c->win, x - size / 2, y + i - size / 2, col);
        mlx_pixel_put(c->mlx, c->win, x + i - size / 2, y + size / 2, col);
        mlx_pixel_put(c->mlx, c->win, x + size / 2, y + i - size / 2, col);
        i++;
    }
}

void update_fps(void)
{
    static int fps = 0;
    static int last_fps = 0;
    static time_t last_time = 0;
    t_cube *c = cube();

    time_t now = time(NULL);
    fps++;
    if (now - last_time >= 1)
    {
        last_time = now;
        last_fps = fps;
        fps = 0;
    }

    char *fps_str = ft_itoa(last_fps);
    mlx_string_put(c->mlx, c->win, 10, 10, 0xFFFFFF, fps_str);
    ft_free(fps_str);
}

int render_scene(t_cube *c)
{
    t_render *r = render();
    r->img_ptr = mlx_new_image(r->mlx, WIDTH, HEIGHT);

    render_view();

    mlx_put_image_to_window(r->mlx, r->win, r->img_ptr, 0, 0);
    mlx_destroy_image(r->mlx, r->img_ptr);

    // render_minimap();
    move_player();
    draw_cross_in_centre();
    update_fps();
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
