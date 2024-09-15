/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:34:36 by escura            #+#    #+#             */
/*   Updated: 2024/09/15 15:56:13 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int mouse_click(int button)
{
    player_mouseclick(button);
    return (0);
}

int mouse_move(int x, int y)
{
    t_render *r = render();

    r->mouse_x = x;
    r->mouse_y = y;
    
    ft_free(player()->hover);
    player()->hover = NULL;

    if(!player()->mouse_hook)
    {
        button_hover(x, y);
        return 0;
    }

    if(!cube()->paused)
        handle_mouse_rotate(x,y);
    // mlx_mouse_move(r->mlx, r->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}