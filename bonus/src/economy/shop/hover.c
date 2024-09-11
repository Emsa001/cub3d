/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:04:55 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 22:44:25 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void shop_item_hover()
{
    t_player *p = player();

    pthread_mutex_lock(&p->money_mutex);
    int price = p->hover->arg;

    if(price > p->money)
        tooltip("Not enough money", 0.4);
    else{
        char *money = ft_itoa(price);
        char *temp = ft_strjoin("Buy for ", money);
        tooltip(temp, 0.4);
        ft_free(money);
    }

    pthread_mutex_unlock(&p->money_mutex);
}