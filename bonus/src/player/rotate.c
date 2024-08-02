/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:39:43 by escura            #+#    #+#             */
/*   Updated: 2024/08/02 20:40:30 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "player.h"

void player_rotate(int x, int y)
{
    // p->z_dir can be from 0 to 1
    // cennter of the screen is 0.5

    t_player *p = player();
	int dx = x - WIDTH / 2;
	int dy = y - HEIGHT / 2;

    p->angle += dx * MOUSE_SENSITIVITY;
    p->z_dir -= dy * MOUSE_SENSITIVITY;
    if (p->z_dir > 1)
        p->z_dir = 1;
    if (p->z_dir < 0)
        p->z_dir = 0;
    if (p->angle > 2 * PI)
        p->angle -= 2 * PI;
    if (p->angle < 0)
        p->angle += 2 * PI;

}