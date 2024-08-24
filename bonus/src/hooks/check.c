/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:15:41 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 15:17:30 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_hooks()
{
    const t_cube *c = cube();
    const t_render *r = render();
    const t_player *p = player();

    if(p->mouse_hook)
        mlx_hook(r->win, MotionNotify, PointerMotionMask, mouse_move, (void *)c);
    else
        mlx_hook(r->win, MotionNotify, PointerMotionMask, NULL, NULL);
}