/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:22:47 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 18:58:30 by escura           ###   ########.fr       */
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
    
    t_string str;
    str.str = "MARKET";
    str.color = 0x00FF00;
    str.size = 1.5;
    str.x = CENTER_WIDTH - 140;
    str.y = CENTER_HEIGHT - 320;

    render_string(&str);    
}

void shop_item_hover(){
    t_player *p = player();
    int price = p->hover->arg;

    if(price > p->money)
        tooltip("Not enough money", 0.4);
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
            
            add_button(&button);
            item_button(&button, 3.2);
        }
        i++;
    }
}

void openCase(int value){
    t_player *p = player();
    t_store *s = p->store;

    if(p->money < value)
        return;
    
    p->money -= value;
    s->open = false;

    int prize = rand() % 100;
    p->money += prize;

    char *money = ft_itoa(prize);

    t_string str;
    str.str = "You won ";
    str.color = 0x00FF00;
    str.size = 0.7;
    str.x = CENTER_WIDTH - 100; 
    str.y = CENTER_HEIGHT - 100;
    str.time = 5000;
    
    render_string_async(&str);

    ft_free(money);
}

void cases(int x, int y){
    const t_textures *t = textures();
    const t_player *p = player();

    int values[3] = {1000, 10000, 50000};

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
            button.function = &openCase;
            button.hover = &shop_item_hover;
            button.arg = values[i];
            button.itemId = p->store->cases[i];

            add_button(&button);
            item_button(&button, 1.5);
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
    
    add_button(&button);
    // item_button(&button,3);
    put_image(t->ui->banner[1], button.x, button.y, 0.9);

}

void open_store()
{
    const t_textures *t = textures();
    const t_player *p = player();

    //  todo: enable
    // if(p->store->can_open == false)
    //     return;

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
            
            add_button(&button);
            item_button(&button, 0.8);
        }
        i++;
    }
}

void shopkeeper(){
    const t_player *p = player();

    float dist = distance(p->x_px / BLOCK_SIZE, p->y_px / BLOCK_SIZE, p->store->x, p->store->y);

    if(dist < 1.5)
        p->store->can_open = true;
    else{
        // p->store->open = false;
        p->store->can_open = false;
    }

    
    if(p->store->can_open){

        t_string str;
        str.str = "Press G to open the shop";
        str.color = 0x00FF00;
        str.size = 0.7;
        str.x = CENTER_WIDTH - 210;
        str.y = HEIGHT -100;

        render_string(&str);
        // render_string("Press G to open the shop", CENTER_WIDTH - 210, HEIGHT -100, 0x00FF00, 0.7);
    }
}