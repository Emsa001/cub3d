/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:04:34 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 17:24:10 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void player_mouseclick(int button)
{
    t_player *p = player();
    t_cube *c = cube();
    
    if(p->mouse_hook){
        if (button == LEFT_CLICK){
            if(p->hand != NULL)
                p->swing = true;
            p->catch = true;
        }
        if(button == RIGHT_CLICK)
        {
            p->catch = false;
            p->catched = false;
        }
    }

    const t_render *r = render();

    int x, y;
    mlx_mouse_get_pos(r->mlx, r->win, &x, &y);
    button_click(button, x, y);
}
