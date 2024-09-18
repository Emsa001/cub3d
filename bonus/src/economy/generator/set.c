/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:42:05 by escura            #+#    #+#             */
/*   Updated: 2024/09/18 19:44:04 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_addmoney(int add, t_generator *gen)
{
    t_cube *c = cube();

    pthread_mutex_lock(&gen->mutex);
    gen->add_money += add;
    pthread_mutex_unlock(&gen->mutex);
    pthread_mutex_lock(&c->add_money_mutex);
    c->add_money += add;
    pthread_mutex_unlock(&c->add_money_mutex);
}