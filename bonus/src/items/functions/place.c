/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:51:19 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 13:57:06 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "items.h"
#include "cub3d.h"

void place(t_item *item)
{
    t_player *p = player();
    
    printf("You placed a %s\n", item->name);

    int x = p->x_px / BLOCK_SIZE;
    int y = p->y_px / BLOCK_SIZE;   
    
    add_sprite("assets/torch/", 9, x,y);
}