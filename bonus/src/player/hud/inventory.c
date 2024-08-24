/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:18:14 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 19:30:32 by escura           ###   ########.fr       */
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

    for (int i = 0; i < 8; i++) {
        // Reset the button
        c->buttons[i] = (t_button){0}; // Sets all fields of the button struct to 0
    }

    for (int i = 0; i < 8; i++)
    {
        if (p->equipped[i] != -1)
        {
            put_image(t->items[p->equipped[i]], x + 25 + (i % 4) * 70, y + 25 + (i / 4) * 70, 1.5);

            t_button *b = ft_malloc(sizeof(t_button));

            // Assign the button properties
            b->x = x + 25 + (i % 4) * 70;
            b->y = y + 25 + (i / 4) * 70;
            b->width = 64;
            b->height = 64;
            b->function = &unequip;
            b->arg = (void *)i;

            if (i < 8)
                c->buttons[i] = *b;

            ft_free(b);
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

    // Clear previous buttons
    for (int i = 8; i < 17; i++) {
        // Reset the button
        c->buttons[i] = (t_button){0}; // Sets all fields of the button struct to 0
    }

    for (int i = 0; i < 9; i++)
    {
        if (p->inventory[i] != -1)
        {
            put_image(t->items[p->inventory[i]], x + 25 + (i % 3) * 70, y + 25 + (i / 3) * 70, 1.5);

            t_button *b = ft_malloc(sizeof(t_button));

            // Assign the button properties
            b->x = x + 25 + (i % 3) * 70;
            b->y = y + 25 + (i / 3) * 70;
            b->width = 64;
            b->height = 64;
            b->function = &useItem;
            b->arg = (void *)i;

            c->buttons[i + 8] = *b;

            // Free the button struct, but not the item struct since it's used later
            ft_free(b);
        }
    }
}
