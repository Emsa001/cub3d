/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:22:47 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 15:30:48 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_store *init_store()
{
    t_store *store = malloc(sizeof(t_store));
    store->open = false;
    store->can_open = false;

    int i = 0;
    while(i < 27)
    {
        store->items[i] = 1;
        i++;
    }

    i = 0;
    while(i < 3)
    {
        store->cases[i] = 146;
        i++;
    }

    i = 0;
    while(i < 2)
    {
        store->generators[i] = 147;
        i++;
    }

    store->x = 7;
    store->y = 1;
    add_sprite("assets/torch/", 9, store->x, store->y);

    return store;
}

void store_window(int x, int y){
    const t_uitextures *t = textures()->ui;
    t_player *p = player();

    p->mouse_hook = false;

    put_image(t->window, x, y, 1.8);
    
    write_string("MARKET", CENTER_WIDTH - 140, CENTER_HEIGHT - 320, 0x00FF00, 1.5);
}

void shop_item_hover(){
    t_player *p = player();
    int index = p->hover->itemId;
    t_item *item = &cube()->items[index];
    const t_textures *t = textures();
    const t_button *b = p->hover;

    // tooltip("kup", 1);
}

void special_offer(int x, int y){
    const t_textures *t = textures();
    const t_player *p = player();

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
            button.function = &useItem;
            button.hover = &shop_item_hover;
            button.arg = (void *)i;
            button.itemId = p->store->items[i];
            
            add_button(button);
            item_button(&button, 3.2);
        }
        i++;
    }
}

void cases(int x, int y){
    const t_textures *t = textures();
    const t_player *p = player();

    int i = 0;
    while(i < 3)
    {
        if (p->store->cases[i] != -1)
        {
            t_button button;
            button.x = x + 315 + (i % 3) * 140;
            button.y = y + 160 + (i / 3) * 140;
            button.width = 128;
            button.height = 128;
            button.function = &useItem;
            button.hover = &shop_item_hover;
            button.arg = (void *)i;
            button.itemId = p->store->cases[i];
            
            add_button(button);
            item_button(&button,1.5);
        }
        i++;
    }
}

void generators(int x, int y){
    const t_textures *t = textures();
    const t_player *p = player();

    int i = 0;

    t_button button;
    button.x = x + t->ui->button->width * 3 + 25;
    button.y = y + 360 + i * t->ui->button->height * 2.2;
    button.width = t->ui->button->width * 6;
    button.height = t->ui->button->height * 2;
    button.function = &useItem;
    button.hover = &shop_item_hover;
    button.arg = (void *)i;
    button.itemId = p->store->cases[i];
    
    add_button(button);
    // item_button(&button,3);
    put_image(t->ui->banner[1], button.x, button.y, 0.9);

}

void open_store()
{
    const t_textures *t = textures();
    const t_player *p = player();

    if(p->store->can_open == false)
        return;

    const int x = CENTER_WIDTH - t->ui->window->width*1.8 /2 ;
    const int y = CENTER_HEIGHT - t->ui->window->height*1.8 /2;

    store_window(x,y);
    special_offer(x,y);
    cases(x,y);
    generators(x,y);

    int i = 0;
    while(i < 21)
    {
        if (p->store->items[i] != -1)
        {

            t_button button;
            button.x = x + 10 + (i % 3) * 70;
            button.y = y + 160 + (i / 3) * 70;
            button.width = 64;
            button.height = 64;
            button.function = &useItem;
            button.hover = &shop_item_hover;
            button.arg = (void *)i;
            button.itemId = p->store->items[i];
            
            add_button(button);
            item_button(&button,0.8);
        }
        i++;
    }
}

void shopkeeper(){
    const t_player *p = player();

    float dist = distance(p->x_px / BLOCK_SIZE, p->y_px / BLOCK_SIZE, p->store->x, p->store->y);

    if(dist < 1)
        p->store->can_open = true;
    else{
        p->store->open = false;
        p->store->can_open = false;
    }

    
    if(p->store->can_open){
        write_string("Press G to open the shop", CENTER_WIDTH - 210, HEIGHT -100, 0x00FF00, 0.7);
    }
}