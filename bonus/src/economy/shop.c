/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:22:47 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 21:30:02 by escura           ###   ########.fr       */
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
    else{
        char *money = ft_itoa(price);
        char *temp = ft_strjoin("Buy for ", money);
        tooltip(temp, 0.4);
        ft_free(money);
    }
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

void openCase(int value) {
    t_player *p = player();
    t_store *store = p->store;
    const t_textures *t = textures();

    if (p->money < value)
        return;

    p->money -= value;
    store->open = false;
    int prize = random_int(0, value * 1.5);
    
    char *tmp = ft_itoa(prize - value);
    char *removeMoneyStr = tmp;
    if(prize - value > 0)
    {
        removeMoneyStr = ft_strjoin("+", ft_itoa(prize - value));
        ft_free(tmp);
    }

    char *displayText = ft_strjoin(removeMoneyStr, "$");

    t_string removeMoneyString;
    removeMoneyString.str = displayText;
    removeMoneyString.color = 0xFFFFFF;
    removeMoneyString.size =  0.4;
    removeMoneyString.x = 80;
    removeMoneyString.y = 60;
    removeMoneyString.time = 1000;

    render_string_async(&removeMoneyString);

    p->money += prize;

    // Display the winning message
    t_string winMessage;
    winMessage.str = "You won";
    winMessage.color = 0xFFFFFF;
    winMessage.size = 1;
    winMessage.x = CENTER_WIDTH - ft_strlen(winMessage.str) * 8;
    winMessage.y = CENTER_HEIGHT - 100;
    winMessage.time = removeMoneyString.time;

    render_string_async(&winMessage);


    t_string prizeMessage;
    ft_memcpy(&prizeMessage, &winMessage, sizeof(t_string));
    prizeMessage.str = displayText;
    prizeMessage.color = 0xF5F5F4;
    prizeMessage.size = 2;
    prizeMessage.x = CENTER_WIDTH - ft_strlen(displayText) * 20;
    prizeMessage.y = CENTER_HEIGHT - 50;
    prizeMessage.clean = displayText;

    render_string_async(&prizeMessage);

    // Determine prize texture based on prize amount
    t_texture *prizeTexture = t->items[158];

    if (prize > 70000) {
        prizeTexture = t->items[162];
    } else if (prize > 50000) {
        prizeTexture = t->items[161];
    } else if (prize > 20000) {
        prizeTexture = t->items[160];
    } else if (prize > 5000) {
        prizeTexture = t->items[159];
    }

    // Render the prize image
    t_image prizeImage;
    prizeImage.img = prizeTexture;
    prizeImage.x = CENTER_WIDTH - 100;
    prizeImage.y = CENTER_HEIGHT - 200;
    prizeImage.size = 10;
    prizeImage.time = winMessage.time - 100;

    render_image_async(&prizeImage);
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