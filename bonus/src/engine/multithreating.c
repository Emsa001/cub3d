/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreating.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:15:01 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 16:11:06 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void clean_main_image(t_render *r){
    mlx_put_image_to_window(r->mlx, r->win, r->img_ptr, 0, 0);
    mlx_destroy_image(r->mlx, r->img_ptr);
}

int render_scene_multithread(t_cube *c){
    t_render *r = render();
    r->img_ptr = mlx_new_image(r->mlx, WIDTH, HEIGHT);
    
    // Create threads
    render_view();
    render_minimap();
    // render_background_thread(c);
    clean_main_image(r);

    move_player();
    update_fps();
    return 0;
}
