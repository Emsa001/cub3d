/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:18:14 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 15:17:19 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void hud_inventory()
{
    const t_textures *t = textures();
    t_player *p = player();

    put_image(t->inventoryPlayer, 0, HEIGHT - t->inventoryPlayer->height);

    if(p->open_inventory)
        open_inventory();
    else
        p->mouse_hook = true;

}

void open_inventory()
{
    t_player *p = player();
    const t_render *r = render();
    const t_textures *t = textures();

    p->mouse_hook = false;
    


    const int x = WIDTH / 2 - t->inventoryGui->width / 2;
    const int y = HEIGHT / 2 - t->inventoryGui->height / 2;
    put_image(t->inventoryGui, x,y);
}