/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shopkeeper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:07:27 by escura            #+#    #+#             */
/*   Updated: 2024/09/18 18:39:56 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void shopkeeper()
{
    t_player *p = player();

    float dist = distance(p->x_px / BLOCK_SIZE, p->y_px / BLOCK_SIZE, p->store->x, p->store->y);
    open_store();
    
    if(dist < 1.5){
        p->GUI_temp = STORE;

        t_string str;
        str.str = "Press G to open the shop";
        str.color = 0x00FF00;
        str.size = 0.7;
        str.x = CENTER_WIDTH - 210;
        str.y = HEIGHT -100;

        render_string(&str);
        // render_string("Press G to open the shop", CENTER_WIDTH - 210, HEIGHT -100, 0x00FF00, 0.7);
    }else if(p->GUI_temp == STORE){
        p->GUI_temp = NONE;
        p->GUI = NONE;
        printf("You left the shop\n");
    }
}