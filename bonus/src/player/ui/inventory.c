/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:18:14 by escura            #+#    #+#             */
/*   Updated: 2024/09/07 19:48:52 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void hud_inventory()
{
    t_player *p = player();
    const t_textures *t = textures();
    const int x = 10;
    const int y = HEIGHT - t->inventoryPlayer->height - 10;
    int i = 0;

    put_image(t->inventoryPlayer, x, y,1);
    while(i < 8)
    {
        if (p->equipped[i] != -1)
        {
            put_image(t->items[p->equipped[i]], x + 25 + (i % 4) * 70, y + 25 + (i / 4) * 70, 1.5);

            t_button button;
            button.x = x + 25 + (i % 4) * 70;
            button.y = y + 25 + (i / 4) * 70;
            button.width = 64;
            button.height = 64;
            button.function = &unequip;
            button.arg = (void *)i;
            button.hover = &item_tooltip;
            button.itemId = p->equipped[i];

            add_button(button);
        }
        i++;
    }

    if(p->open_inventory)
        open_inventory();
}

void open_inventory() {
    t_player *p = player();
    const t_textures *t = textures();
    const int x = (WIDTH / 2 - t->inventoryGui->width / 2);
    const int y = (HEIGHT / 2 - t->inventoryGui->height / 2);

    p->mouse_hook = false;
    write_string("Inventory", x, y - 25, 0xFFFFFF, 0.6);
    put_image(t->inventoryGui, x, y, 1);

    int i = 0;
    while(i < 9)
    {
        if (p->inventory[i] != -1)
        {
            put_image(t->items[p->inventory[i]], x + 25 + (i % 3) * 70, y + 25 + (i / 3) * 70, 1.5);

            t_button button;
            button.x = x + 25 + (i % 3) * 70;
            button.y = y + 25 + (i / 3) * 70;
            button.width = 64;
            button.height = 64;
            button.function = &useItem;
            button.hover = &item_tooltip;
            button.arg = (void *)i;
            button.itemId = p->inventory[i];
            
            add_button(button);
        }
        
        i++;
    }
}