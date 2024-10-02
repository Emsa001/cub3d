/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:15:01 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 19:21:13 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void create_image(t_render *r, int width, int height)
{
    r->img_ptr = mlx_new_image(r->mlx, width, height);
    r->data = mlx_get_data_addr(r->img_ptr, &r->bpp, &r->size_line, &r->endian);
}

static void show_image(int x, int y)
{
    const t_render *r = render();
    mlx_put_image_to_window(r->mlx, r->win, r->img_ptr, x, y);
}

static void render_queue(){
    t_render *r = render();

    put_image_queue(r);
    put_string_queue(r);
    async_queue();
}

int render_scene_multithread(void)
{
    t_player *p = player();

    p->mouse_hook = true;

    render_view(cube());
    render_player();
    economy_loop();
    
    if(!is_paused() && p->gui != MATH)
        move_player();
    
    render_queue(render());

    update_fps();
    hide_mouse();
    
    execute_button_hover();
    show_image(0, 0);
    return 0;
}
