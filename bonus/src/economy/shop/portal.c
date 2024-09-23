/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:46:59 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 17:46:39 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void opening()
{
    const t_cube *c = cube();
    open_portal(c->next_portal);
}

void buy_portalkey(){
    t_player *p = player();
    t_cube *c = cube();
    int time = 5000;

    if(money() < 10000)
        return;
    
    p->GUI = NONE;
    add_money(-10000);

    t_location *l = ft_calloc(1, sizeof(t_location));
    l->x = CENTER_WIDTH - 32;
    l->y = CENTER_HEIGHT - 32;

    string_timer(time,l);
    ft_wait(time, &opening);
    
    t_string str = {0};
    str.str = "You have powered up the portal!";
    str.x = CENTER_WIDTH - 500;
    str.y = HEIGHT - 200;
    str.color = 0x00FF00;
    str.size = 1;
    str.time = time;
    render_string_async(&str);
    
    t_texture *t = textures()->ui->button_long;

    for(int i = 0; i < 5; i++){
        t_image img;
        img.img = t;
        img.x = CENTER_WIDTH - 555 + (i * t->width - ((i-1) * 4));
        img.y = HEIGHT - 225;
        img.size = 1;
        img.time = time;
        render_image_async(&img);
    }

    c->next_portal = c->next_portal - 1;
}

void buy_portal_tooltip(){
    const t_cube *c = cube();
    tooltip("10000 $",0.4);
}

void portal_offer(int x, int y)
{
    const t_cube *c = cube();
    const t_textures *t = textures();
    const t_player *p = player();

    if(c->next_portal == 0)
        return ;
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
