/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:15:01 by escura            #+#    #+#             */
/*   Updated: 2024/09/07 17:16:13 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void create_image(t_render *r, int width, int height)
{
    r->img_ptr = mlx_new_image(r->mlx, width, height);
    r->data = mlx_get_data_addr(r->img_ptr, &r->bpp, &r->size_line, &r->endian);
}

void clean_image(t_render *r)
{
    show_image(r, 0, 0);
    mlx_destroy_image(r->mlx, r->img_ptr);
    r->img_ptr = NULL;
}

void show_image(t_render *r, int x, int y)
{
    mlx_put_image_to_window(r->mlx, r->win, r->img_ptr, x, y);
}

int render_scene_multithread(t_cube *c)
{
    t_render *r = render();
    create_image(r, WIDTH, HEIGHT);

    // Create threads
    render_view();
    // render_background_thread(c);
    render_player();
    run_async_queue();
    
    if(!c->paused)
        move_player();
        
    clean_image(r);
    check_hooks();
    update_fps();
    return 0;
}
