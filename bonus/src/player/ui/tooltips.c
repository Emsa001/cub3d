/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tooltips.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:41:37 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 18:32:26 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void tooltip(char *string, float size)
{
    t_cube *c = cube();
    t_player *p = player();
    t_texture *tooltip_bg = textures()->tooltip_bg;
    const t_render *r = render();

    put_image(tooltip_bg, r->mouse_x - 10, r->mouse_y - 40, 3);

    t_string str = {0};
    str.str = string;
    str.color = 0xFFFFFF;
    str.size = size;
    str.x = r->mouse_x + size * 20;
    str.y = r->mouse_y - (size) * 50;
    
    render_string(&str);
    // render_string(string, r->mouse_x + size * 20, r->mouse_y - (size) * 50, 0xFFFFFF, size);
}

void render_tooltip()
{
    t_player *p = player();
    
    if(p->hover != NULL){
        t_button *button = p->hover;
        if(button->hover != NULL)
            ((void (*)(void*))button->hover)(button->arg);
    } 
}