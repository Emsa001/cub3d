/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:30:29 by escura            #+#    #+#             */
/*   Updated: 2024/07/22 18:30:59 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float minimap_center_x(void)
{
    const t_minimap *m = minimap();
    return m->x + MINIMAP_PIXEL_WIDTH / 2.0f;
}

float minimap_center_y(void)
{
    const t_minimap *m = minimap();
    return m->y + MINIMAP_PIXEL_HEIGHT / 2.0f;
}