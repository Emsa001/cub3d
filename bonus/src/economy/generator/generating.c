/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:37:10 by escura            #+#    #+#             */
/*   Updated: 2024/09/20 12:39:21 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void generator_generating(t_async *current)
{
    t_generator *gen = (t_generator *)current->arg;

    pthread_mutex_lock(&gen->mutex);

    double money_to_add = (gen->add_money / 5.0) * gen->speed;
    add_money(money_to_add);
    gen->generated += money_to_add;

    // gen->loop += gen->speed;

    pthread_mutex_unlock(&gen->mutex);
}
