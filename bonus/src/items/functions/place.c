/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:51:19 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 19:38:42 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	place(t_item *item)
{
	t_player	*p = player();
	const int		x = p->x_px / BLOCK_SIZE;
	const int		y = p->y_px / BLOCK_SIZE;

	printf("You placed a %s\n", item->name);
	add_facing_sprite("assets/torch/", 9, x, y);
	p->equipped[item->props.slot] = -1;
	p->hand = NULL;

}
