/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:15:41 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 15:23:37 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_hooks()
{
    const t_cube *c = cube();
    const t_render *r = render();
    const t_player *p = player();

    if(p->mouse_hook){
        mlx_hook(r->win, MotionNotify, PointerMotionMask, mouse_move, (void *)c);
        mlx_mouse_hide(r->mlx, r->win);
    }
    else{
        mlx_hook(r->win, MotionNotify, PointerMotionMask, NULL, NULL);
        mlx_mouse_show(r->mlx, r->win);
    }
}