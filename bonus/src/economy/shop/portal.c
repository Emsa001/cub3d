/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:46:59 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 22:47:34 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void portal_offer(int x, int y)
{
    const t_textures *t = textures();
    const t_player *p = player();

    t_button button;
    button.x = x + t->ui->button->width * 3 + 25;
    button.y = y + 360;
    button.width = t->ui->button->width * 5 + 25;
    button.height = t->ui->button->height * 3;
    button.function = NULL;
    button.hover = &shop_item_hover;
    
    add_button(&button);
    put_image(t->ui->banner[1], button.x, button.y, 0.9);

}
