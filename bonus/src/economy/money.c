/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   money.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:09:25 by escura            #+#    #+#             */
/*   Updated: 2024/09/18 19:16:34 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hud_currency(void)
{
    t_cube *c = cube();
    t_player *p = player();
    const t_textures *t = textures();
    const t_render *r = render();
    
    int i = 0;

    if (t->ui && t->ui->button) {
        while(i <= 3){
            put_image(t->ui->button, (i * (t->ui->button->width - 15)), 5, 1);
            i++;
        }
    }

    // money texture
    put_image(&t->items[66], 10, 12, 2);

    pthread_mutex_lock(&c->add_money_mutex);
    pthread_mutex_lock(&p->money_mutex);

    char *money = ft_itoa(p->money);
    char *add = ft_itoa(c->add_money);

    pthread_mutex_unlock(&p->money_mutex);
    pthread_mutex_unlock(&c->add_money_mutex);

    put_string("+", 80, 15, 0xFFFFFF, 0.4);
    put_string(add, 95, 15, 0xFFFFFF, 0.4);
    put_string(money, 80, 37, 0xffbf00, 0.5);

    ft_free(money);
    ft_free(add);
}