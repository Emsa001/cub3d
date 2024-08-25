/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:18:14 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 18:15:21 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void hud_inventory()
{
    const t_textures *t = textures();
    t_player *p = player();
    t_cube *c = cube();
    
    int x = 10;
    int y = HEIGHT - t->inventoryPlayer->height - 10;

    put_image(t->inventoryPlayer, x, y,1);

    // Free the old buttons
    
    for (int i = 0; i < 8; i++)
    {
        if (p->equipped[i] != -1)
        {
            put_image(t->items[p->equipped[i]], x + 25 + (i % 4) * 70, y + 25 + (i / 4) * 70, 1.5);

            t_button button;

            // Assign the button properties
            button.x = x + 25 + (i % 4) * 70;
            button.y = y + 25 + (i / 4) * 70;
            button.width = 64;
            button.height = 64;
            button.function = &unequip;
            button.arg = (void *)i;
            button.itemId = p->equipped[i];

            add_button(button);
        }
    }

    if(p->open_inventory)
        open_inventory();
    else
        p->mouse_hook = true;
}

void open_inventory() {
    t_player *p = player();
    t_cube *c = cube();
    const t_render *r = render();
    const t_textures *t = textures();

    p->mouse_hook = false;
    
    const int x = (WIDTH / 2 - t->inventoryGui->width / 2);
    const int y = (HEIGHT / 2 - t->inventoryGui->height / 2);

    write_string("Inventory", x, y - 25, 0xFFFFFF, 0.6);
    put_image(t->inventoryGui, x, y, 1);

    for (int i = 0; i < 9; i++)
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
            button.arg = (void *)i;
            button.itemId = p->inventory[i];
            
            add_button(button);
        }
    }
}