/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:46:59 by escura            #+#    #+#             */
/*   Updated: 2024/09/17 17:05:18 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void opening()
{
    open_portal(1);
}

void buy_portalkey(){
    t_player *p = player();
    t_cube *c = cube();

    if(money() < 10000)
        return;
    add_money(-10000);
    ft_wait(2000, &opening);
    printf("You bought a portal key\n");
}

void buy_portal_tooltip(){
    tooltip("10000 $",0.4);
}

void portal_offer(int x, int y)
{
    const t_textures *t = textures();
    const t_player *p = player();

    t_button button;
    button.x = x + t->ui->button->width * 3 + 25;
    button.y = y + 360;
    button.width = t->ui->button->width * 5 + 25;
    button.height = t->ui->button->height * 3;
    button.function = &buy_portalkey;
    button.hover = &buy_portal_tooltip;
    
    add_button(&button);
    put_image(t->open_portal, button.x, button.y, 0.9);
}
