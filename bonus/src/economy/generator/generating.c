/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:37:10 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 17:34:24 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void generator_generating(t_async *current)
{
    if(is_paused())
        return;

    t_generator *gen = (t_generator *)current->arg;

    pthread_mutex_lock(&gen->mutex);

    double money_to_add = (gen->add_money / 5.0) * gen->speed;
    add_money(money_to_add);
    gen->generated += money_to_add;

    int x = random_int(gen->random * 5,100);
    if(gen->random > 0 && x == 100){
        const int add = random_int(10, 100000 * gen->random);
        add_money(add);
        gen->generated += add;
        
        char *addstr = ft_itoa(add);

        t_string extra = {0};
        extra.str = ft_strjoin("+", addstr);
        extra.color = 0xFFFFFF;
        extra.size = 0.5;
        extra.x = 80;
        extra.y = 60;
        extra.time = 1000;
        extra.background = 0x2A2E37;
        extra.padding = 1;

        render_string_async(&extra);
        ft_free(addstr);

    }

    // gen->loop += gen->speed;

    pthread_mutex_unlock(&gen->mutex);
}
