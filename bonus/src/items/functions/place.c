/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:51:19 by escura            #+#    #+#             */
/*   Updated: 2024/09/27 18:18:58 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	place(t_item *item)
{
	const int	x = player()->x_px / BLOCK_SIZE;
	const int	y = player()->y_px / BLOCK_SIZE;

	printf("You placed a %s\n", item->name);
	add_facing_sprite("assets/torch/", 9, x, y);
	player()->equipped[item->props.slot] = -1;
	player()->hand = NULL;
}
