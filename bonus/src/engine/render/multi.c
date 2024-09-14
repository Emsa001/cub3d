/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:15:01 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 21:06:54 by btvildia         ###   ########.fr       */
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
    mlx_destroy_image(r->mlx, r->img_ptr);
    r->img_ptr = NULL;
}

void clear_image(t_render *r)
{
    ft_bzero(r->data, WIDTH * HEIGHT * 4);
}

void show_image(t_render *r, int x, int y)
{
    mlx_put_image_to_window(r->mlx, r->win, r->img_ptr, x, y);
}

void render_queue(t_render *r){
    put_image_queue(r);
    put_string_queue(r);
    execute_functions_queue(r);
}

int render_scene_multithread(void)
{
    t_render *r = render();
    t_cube *c = cube();

    if(c->map->editor_mode){
        // clear_image(r);
        destroy_buttons();
        map_editor_enter();
        render_queue(r);
        render_tooltip();

        // update_fps();
        show_image(r, 0, 0);
        return 0;
    }

    // clear_image(r);
    render_view(c);
    render_player();
    shopkeeper();
    
    if(!c->paused)
        move_player();
    
    render_queue(r);

    update_fps();
    // check_hooks();
    
    render_tooltip();
    show_image(r, 0, 0);
    return 0;
}
