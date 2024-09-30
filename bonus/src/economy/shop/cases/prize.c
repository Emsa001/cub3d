/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prize.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:27:23 by escura            #+#    #+#             */
/*   Updated: 2024/09/30 20:42:11 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*getDisplayText(int prize, int value)
{
	char	*displayText;
	char	*tmp;
	char	*removeMoneyStr;

    tmp = ft_itoa(prize - value);
    removeMoneyStr = ft_strdup(tmp);
    ft_free(tmp);
	if (prize - value > 0)
		displayText = ft_strjoin("+", removeMoneyStr);
	else
		return removeMoneyStr;
    ft_free(removeMoneyStr);
	return displayText;
}

void displayPrizeMessage(int prize, int value)
{
    char *displayText = getDisplayText(prize, value);
    t_string string;
    if (displayText == NULL)
        return;

    string = (t_string){ 0 };
    string.str = ft_strdup(displayText);
    string.color = 0xFFFFFF;
    string.size =  0.4;
    string.x = 80;
    string.y = 60;
    string.time = 1000;
    render_string_async(&string);

    string.str = "You got";
    string.size = 1;
    string.x = CENTER_WIDTH - ft_strlen(string.str) * 8;
    string.y = CENTER_HEIGHT - 200;

    render_string_async(&string);

    string.str = displayText;
    string.size = 2;
    string.x = CENTER_WIDTH - ft_strlen(string.str) * 20;
    string.y =  CENTER_HEIGHT + 120;
    render_string_async(&string);
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