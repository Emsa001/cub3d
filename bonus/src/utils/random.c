/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:22:51 by escura            #+#    #+#             */
/*   Updated: 2024/09/24 19:47:20 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	random_int(int min, int max)
{
	return ((rand() % (max - min + 1)) + min);
}

double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}
