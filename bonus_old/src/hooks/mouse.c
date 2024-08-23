/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:34:36 by escura            #+#    #+#             */
/*   Updated: 2024/08/03 17:05:14 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

int mouse_click(int button)
{
    player_mouseclick(button);
    return (0);
}

int mouse_move(int x, int y)
{
    const t_render *r = render();
    player_rotate(x,y);

	mlx_mouse_move(r->mlx, r->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}