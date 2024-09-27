/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:22:47 by escura            #+#    #+#             */
/*   Updated: 2024/09/27 18:48:28 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void store_window(int x, int y){
    const t_uitextures *t = textures()->ui;

    put_image(t->window, x, y, 1.8);
    
    t_string str = {0};
    str.str = "MARKET";
    str.color = 0x00FF00;
    str.size = 1.5;
    str.x = CENTER_WIDTH - 140;
    str.y = CENTER_HEIGHT - 320;

    render_string(&str);    
}

static void init_shop_items(int x, int y, t_player *p){
    int i = 0;
    while(i < 21)
    {
        if (p->store->items[i] != -1)
        {

            t_button button = { 0 };
            button.x = x + 10 + (i % 3) * 70;
            button.y = y + 160 + (i / 3) * 70;
            button.width = 64;
            button.height = 64;
            button.function = NULL;
            button.hover = &shop_item_hover;
            button.arg = (void *)(intptr_t)(i * 1000);
            button.itemId = p->store->items[i];
            
            add_button(&button);
            item_button(&button, 0.8);
        }
        i++;
    }
}

void open_store()
{
    const t_textures *t = textures();
    t_player *p = player();

    if(p->GUI != STORE)
        return;

    p->mouse_hook = false;
     
    const int x = CENTER_WIDTH - t->ui->window->width*1.8 /2 ;
    const int y = CENTER_HEIGHT - t->ui->window->height*1.8 /2;

    store_window(x,y);
    special_offer(x,y);
    cases(x,y);
    portal_offer(x,y);
    init_shop_items(x,y,p);    
}
