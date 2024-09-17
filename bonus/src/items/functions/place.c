/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:51:19 by escura            #+#    #+#             */
/*   Updated: 2024/09/17 17:56:17 by btvildia         ###   ########.fr       */
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
    
    add_facing_sprite("assets/torch/", 9, x,y);
}