/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:51:19 by escura            #+#    #+#             */
/*   Updated: 2024/10/01 14:58:19 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	place(t_item *item)
{
	const float	x = (cos(player()->angle) * 1) + (player()->x_px / BLOCK_SIZE);
	const float	y = (sin(player()->angle) * 1) + (player()->y_px / BLOCK_SIZE);

	printf("You placed a %s in %f %f\n", item->name, x, y);
	add_facing_sprite("assets/torch/", 9, x, y);
	player()->equipped[item->props.slot] = -1;
	player()->hand = NULL;
}
