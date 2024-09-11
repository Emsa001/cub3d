/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:22:51 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 20:23:04 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int random_int(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

float random_float(float min, float max)
{
    return ((float)rand() / RAND_MAX) * (max - min) + min;
}