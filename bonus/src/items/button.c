/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:09:10 by escura            #+#    #+#             */
/*   Updated: 2024/09/13 20:17:51 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void item_button(t_button *button, float size)
{
    const t_textures *t = textures();
    const t_player *p = player();

    // Check if the button is being hovered over
    if(p->hover && p->hover->x == button->x && p->hover->y == button->y)
        put_image(t->ui->button_hover, button->x, button->y, size);
    else
        put_image(t->ui->button, button->x, button->y, size);

    // put_image(button->texture, button->x, button->y, size);

    // Calculate the position to center the item inside the button
    t_texture item_texture = t->items[button->itemId];
    int item_width = item_texture.width * size*2;
    int item_height = item_texture.height * size*2.3;

    int item_x = button->x + (button->width - item_width) / 2;
    int item_y = button->y + (button->height - item_height) / 2;

    // Draw the item centered inside the button
    put_image(&item_texture, item_x, item_y, size*2);
}
