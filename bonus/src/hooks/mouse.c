/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:34:36 by escura            #+#    #+#             */
/*   Updated: 2024/08/02 20:45:49 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

int mouse_click(int button)
{
    t_player *p = player();
    if (button == LEFT_CLICK)
        p->catch = true;
    if(button == RIGHT_CLICK)
    {
        p->catch = false;
        p->catched = false;
    }
    return (0);
}

int mouse_move(int x, int y)
{
    const t_render *r = render();
    player_rotate(x,y);

	mlx_mouse_move(r->mlx, r->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}