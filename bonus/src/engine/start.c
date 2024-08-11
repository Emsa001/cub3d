/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:21:09 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 16:12:40 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int render_scene(t_cube *c)
{
    t_render *r = render();
    r->img_ptr = mlx_new_image(r->mlx, WIDTH, HEIGHT);

    render_view();

    mlx_put_image_to_window(r->mlx, r->win, r->img_ptr, 0, 0);
    mlx_destroy_image(r->mlx, r->img_ptr);

    // render_minimap();
    move_player();
    render_player();
    return 0;
}

void start_game(void)
{
    t_cube *c = cube();
    t_render *r = render();
    // print_map_info();
    r->win = mlx_new_window(r->mlx, WIDTH, HEIGHT, "Cub3D");
    init_hooks();
}
