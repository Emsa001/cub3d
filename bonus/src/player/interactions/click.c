/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:04:34 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 19:31:03 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void player_mouseclick(int button)
{
    t_player *p = player();
    t_cube *c = cube();
    
    if (button == LEFT_CLICK)
        p->catch = true;
    if(button == RIGHT_CLICK)
    {
        p->catch = false;
        p->catched = false;
    }

    const t_render *r = render();

    int x, y;
    mlx_mouse_get_pos(r->mlx, r->win, &x, &y); // Corrected

    printf("Mouse click at x: %d, y: %d\n", x, y);

    for(int i = 0; i < 32; i++)
    {
        if(x >= c->buttons[i].x && x <= c->buttons[i].x + c->buttons[i].width &&
           y >= c->buttons[i].y && y <= c->buttons[i].y + c->buttons[i].height)
        {
            if (c->buttons[i].function != NULL)
            {
                printf("Function pointer is valid. Calling function...\n");
                ((void (*)(void*))c->buttons[i].function)(c->buttons[i].arg);
            }
        }
    }
}
