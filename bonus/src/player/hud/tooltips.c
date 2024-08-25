/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tooltips.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:41:37 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 19:03:14 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void hud_tooltips()
{
    t_cube *c = cube();
    t_player *p = player();
    t_texture *tooltip_bg = textures()->tooltip_bg;
    const t_render *r = render();

    if(p->cursorItem != NULL){

        char *tooltip = p->cursorItem->name;
        float size = p->cursorItem->fontSize;

        put_image(tooltip_bg, r->mouse_x - 10, r->mouse_y - 40, 3);
        write_string(tooltip, r->mouse_x + size * 20, r->mouse_y - size * 50, 0xFFFFFF, size);
    }
}