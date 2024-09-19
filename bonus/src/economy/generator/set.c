/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:42:05 by escura            #+#    #+#             */
/*   Updated: 2024/09/19 17:37:22 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_addmoney(int add)
{
    t_cube *c = cube();
    
    pthread_mutex_lock(&c->add_money_mutex);
    c->add_money += add;
    pthread_mutex_unlock(&c->add_money_mutex);
}