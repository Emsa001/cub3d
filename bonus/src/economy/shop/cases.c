/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:04:42 by escura            #+#    #+#             */
/*   Updated: 2024/09/13 21:57:38 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void updatePlayerMoney(t_player *p, int amount)
{
    pthread_mutex_lock(&p->money_mutex);
    p->money += amount;
    pthread_mutex_unlock(&p->money_mutex);
}

void displayPrizeMessage(int prize, int value)
{
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

    t_string winMessage;
    winMessage.str = "You got";
    winMessage.color = 0xFFFFFF;
    winMessage.size = 1;
    winMessage.x = CENTER_WIDTH - ft_strlen(winMessage.str) * 8;
    winMessage.y = CENTER_HEIGHT - 200;
    winMessage.time = removeMoneyString.time;

    render_string_async(&winMessage);

    t_string prizeMessage;
    ft_memcpy(&prizeMessage, &winMessage, sizeof(t_string));
    prizeMessage.str = displayText;
    prizeMessage.color = 0xF5F5F4;
    prizeMessage.size = 2;
    prizeMessage.x = CENTER_WIDTH - ft_strlen(displayText) * 20;
    prizeMessage.y = CENTER_HEIGHT + 100;
    prizeMessage.clean = displayText;

    render_string_async(&prizeMessage);

    ft_free(removeMoneyStr);
}

t_texture determinePrizeTexture(const t_textures *t, int prize)
{
    t_texture prizeTexture = t->items[65];

    if (prize > 70000) {
        prizeTexture = t->items[70];
    } else if (prize > 50000) {
        prizeTexture = t->items[69];
    } else if (prize > 20000) {
        prizeTexture = t->items[68];
    } else if (prize > 5000) {
        prizeTexture = t->items[66];
    }

    return prizeTexture;
}

void renderPrizeImage(t_texture *prizeTexture, int time)
{
    // Render the prize image
    t_image prizeImage;
    prizeImage.img = prizeTexture;
    prizeImage.x = CENTER_WIDTH - 100;
    prizeImage.y = CENTER_HEIGHT - 200;
    prizeImage.size = 10;
    prizeImage.time = time - 100;

    render_image_async(&prizeImage);
}

void openCase(void *arg)
{
    t_player *p = player();
    t_store *store = p->store;
    const t_textures *t = textures();
    const int value = (int)(intptr_t)arg;

    pthread_mutex_lock(&p->money_mutex);
    if (p->money < value)
    {
        pthread_mutex_unlock(&p->money_mutex);
        return;
    }
    pthread_mutex_unlock(&p->money_mutex);

    updatePlayerMoney(p, -value);
    store->open = false;
    int prize = random_int(0, value * 2);

    displayPrizeMessage(prize, value);
    updatePlayerMoney(p, prize);

    t_texture prizeTexture = determinePrizeTexture(t, prize);
    renderPrizeImage(&prizeTexture, 1000);
}

void cases(int x, int y)
{
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
            button.arg = (void *)(intptr_t)values[i];
            button.itemId = p->store->cases[i];

            add_button(&button);
            item_button(&button, 1.5);
        }
        i++;
    }
}
