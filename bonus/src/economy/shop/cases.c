/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:04:42 by escura            #+#    #+#             */
/*   Updated: 2024/09/18 18:02:26 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void displayPrizeMessage(int prize, int value)
{
    char *tmp = ft_itoa(prize - value);
    char *removeMoneyStr = ft_strdup(tmp);

    if(prize - value > 0)
    {
        removeMoneyStr = ft_strjoin("+", ft_itoa(prize - value));
        ft_free(tmp);
    }

    char *displayText = ft_strjoin(removeMoneyStr, "$");

    t_string removeMoneyString = { 0 };
    removeMoneyString.str = ft_strdup(displayText);
    removeMoneyString.color = 0xFFFFFF;
    removeMoneyString.size =  0.4;
    removeMoneyString.x = 80;
    removeMoneyString.y = 60;
    removeMoneyString.time = 1000;
    render_string_async(&removeMoneyString);

    t_string winMessage = {0};
    winMessage.str = "You got";
    winMessage.color = 0xFFFFFF;
    winMessage.size = 1;
    winMessage.x = CENTER_WIDTH - ft_strlen(winMessage.str) * 8;
    winMessage.y = CENTER_HEIGHT - 200;
    winMessage.time = removeMoneyString.time;

    render_string_async(&winMessage);

    t_string winMessage2 = { 0 };
    winMessage2.str = ft_strdup(displayText);
    winMessage2.color = 0xFFFFFF;
    winMessage2.size = 2;
    winMessage2.x = CENTER_WIDTH - ft_strlen(winMessage2.str) * 20;
    winMessage2.y =  CENTER_HEIGHT + 120;
    winMessage2.time = 1000;
    render_string_async(&winMessage2);

    ft_free(removeMoneyStr);
}

t_texture *determinePrizeTexture(int prize)
{
    t_textures *t = textures();
    t_texture *prizeTexture = &(t->items[66]);

    if (prize > 70000) {
        prizeTexture = &(t->items[70]);
    } else if (prize > 50000) {
        prizeTexture = &(t->items[69]);
    } else if (prize > 20000) {
        prizeTexture = &(t->items[68]);
    } else if (prize > 5000) {
        prizeTexture = &(t->items[67]);
    }

    return prizeTexture;
}

void renderPrizeImage(t_texture *prizeTexture, int time)
{
    // Render the prize image
    t_image prizeImage = { 0 };
    prizeImage.img = prizeTexture;
    prizeImage.x = CENTER_WIDTH - 100;
    prizeImage.y = CENTER_HEIGHT - 200;
    prizeImage.size = 10;
    prizeImage.time = time;

    render_image_async(&prizeImage);
}

void cooldown_end(t_async *async)
{
    t_store *store = player()->store;
    pthread_mutex_lock(&store->case_mutex);
    store->case_cooldown = false;
    pthread_mutex_unlock(&store->case_mutex);
}

void start_cooldown(t_async *async)
{
    t_store *store = player()->store;
    pthread_mutex_lock(&store->case_mutex);
    store->case_cooldown = true;
    pthread_mutex_unlock(&store->case_mutex);
}

void openCase(void *arg)
{
    t_player *p = player();
    t_store *store = p->store;
    const int value = (int)(intptr_t)arg;

    pthread_mutex_lock(&store->case_mutex);
    if(store->case_cooldown){
        pthread_mutex_unlock(&store->case_mutex);
        tooltip("Cooldown",1);
        return;
    }
    pthread_mutex_unlock(&store->case_mutex);
   

    t_async *async = new_async();
    async->process = &start_cooldown;
    async->end = &cooldown_end;
    async->time = 1500;
    start_async(async);


    pthread_mutex_lock(&p->money_mutex);
    if (p->money < value)
    {
        pthread_mutex_unlock(&p->money_mutex);
        return;
    }
    pthread_mutex_unlock(&p->money_mutex);

    add_money(-value);
    p->GUI = NONE;
    int prize = random_int(0, value * 2);

    displayPrizeMessage(prize, value);
    add_money(prize);

    t_texture *prizeTexture = determinePrizeTexture(prize);
    renderPrizeImage(prizeTexture, 1000);
}

void cases(int x, int y)
{
    const t_textures *t = textures();
    const t_player *p = player();

    int values[3] = {1000, 10000, 50000};

    int i = 0;
    while(i < 3)
    {
        t_button button;
        button.x = x + 315 + (i % 3) * 140;
        button.y = y + 160 + (i / 3) * 140;
        button.width = 128;
        button.height = 128;
        button.function = &openCase;
        button.hover = &shop_item_hover;
        button.arg = (void *)(intptr_t)values[i];
        button.itemId = 71;

        add_button(&button);
        item_button(&button, 1.5);
        i++;
    }
}
