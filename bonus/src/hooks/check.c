/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:15:41 by escura            #+#    #+#             */
/*   Updated: 2024/09/13 20:45:29 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_hooks()
{
    const t_cube *c = cube();
    const t_render *r = render();
    const t_player *p = player();

    if(p->mouse_hook){
        mlx_mouse_hide(r->mlx, r->win);
        mlx_mouse_move(r->mlx, r->win, CENTER_WIDTH, CENTER_HEIGHT);
    }
    else{
        mlx_mouse_show(r->mlx, r->win);
    }
}