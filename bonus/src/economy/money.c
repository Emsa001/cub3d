/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   money.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:09:25 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 17:59:33 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hud_currency(void)
{
	const t_textures *t = textures();
	const t_player *p = player();
	const t_render *r = render();
    int i = 0;

    while(i <= 3){
        put_image(t->ui->button, (i * (t->ui->button->width - 15)), 5, 1);
        i++;
    }

	put_image(t->items[158], 10, 12, 2);
    char *money = ft_itoa(p->money);

    t_string str;
    str.str = money;
    str.color = 0xffbf00;
    str.size = 0.5;
    str.x = 80;
    str.y = 37;

    write_string(&str);
    ft_free(money);
}