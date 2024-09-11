/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:06:59 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 22:46:57 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void activate_special(void *arg){
    int price = (int)arg;
}

void special_offer(int x, int y)
{
    const t_textures *t = textures();
    const t_player *p = player();

    int *prices = {
        10000, 200000
    };

    int i = 0;
    while(i < 2)
    {
        if (p->store->items[i] != -1)
        {
            t_button button;
            
            button.x = x + 810;
            button.y = y + 160 + i * t->ui->button->height * 3.2;
            button.width = t->ui->button->width * 3.2;
            button.height = t->ui->button->height * 3.2;
            
            button.function = &activate_special;
            button.hover = &shop_item_hover;
            button.arg = (void *)1000;
            button.itemId = p->store->items[i];
            
            add_button(&button);
            item_button(&button, 3.2);
        }
        i++;
    }
}
