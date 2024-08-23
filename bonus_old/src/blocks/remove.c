/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:14:44 by btvildia            #+#    #+#             */
/*   Updated: 2024/07/21 13:14:46 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void remove_block(float angle)
{
    t_player *p = player();

    if(p->catched)
        return;

    t_cube *c = cube();
    int id = get_block_id(c->map->blocks, p->x, p->y, angle);
    t_block *new_blocks;
    t_block *tmp;
    t_block *blocks = c->map->blocks;
    int i = 0;
    int j = 0;
    
    if(id == -1)
        return;
    new_blocks = ft_malloc(sizeof(t_block) * (block_count(c->map, '2')));
    while(blocks[i].x != -1)
    {
        if(i != id)
        {
            new_blocks[j] = blocks[i];
            j++;
        }
        i++;
    }
    new_blocks[j].x = -1;
    new_blocks[j].y = -1;
    new_blocks[j].id = -1;
    new_blocks[j].type = '\0';
    tmp = c->map->blocks;
    c->map->blocks = new_blocks;
    ft_free(tmp);
}