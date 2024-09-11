/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tooltips.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:41:37 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 18:03:06 by escura           ###   ########.fr       */
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

    t_string str;
    str.str = string;
    str.color = 0xFFFFFF;
    str.size = size;
    str.x = r->mouse_x + size * 20;
    str.y = r->mouse_y - (size) * 50;
    
    write_string(&str);
    // write_string(string, r->mouse_x + size * 20, r->mouse_y - (size) * 50, 0xFFFFFF, size);
}