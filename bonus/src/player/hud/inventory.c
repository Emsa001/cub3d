/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:18:14 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 16:29:12 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void hud_inventory()
{
    const t_textures *t = textures();
    t_player *p = player();

    put_image(t->inventoryPlayer, 10, HEIGHT - t->inventoryPlayer->height - 10);

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
    
    const int x = (WIDTH / 2 - t->inventoryGui->width / 2);
    const int y = (HEIGHT / 2 - t->inventoryGui->height / 2);

    write_string("Inventory", x - 20, y - 50, 0x00FF00);
    put_image(t->inventoryGui, x,y);
}