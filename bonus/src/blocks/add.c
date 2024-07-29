/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:14:30 by btvildia            #+#    #+#             */
/*   Updated: 2024/07/21 13:14:32 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void add_block(float angle)
{
    const t_player *p = player();
    int i;
    float x = 0;
    float y = 0;

    x = p->x - 0.5 + 2.5 * cos(angle);
    y = p->y - 0.5 + 2.5 * sin(angle);
    t_block *new_blocks;
    t_block *tmp;
    t_block *blocks = cube()->map->blocks;

    i = 0;
    while (blocks[i].x != -1)
        i++;
    new_blocks = ft_malloc(sizeof(t_block) * (i + 2));
    i = 0;
    while (blocks[i].x != -1)
    {
        new_blocks[i] = blocks[i];
        i++;
    }
    new_blocks[i].x = x;
    new_blocks[i].y = y;
    new_blocks[i].z = 0;
    new_blocks[i].id = i;
    new_blocks[i].type = '2';
    new_blocks[i + 1].x = -1;
    new_blocks[i + 1].y = -1;
    new_blocks[i + 1].id = -1;
    new_blocks[i + 1].type = '\0';
    tmp = cube()->map->blocks;
    cube()->map->blocks = new_blocks;
    ft_free(tmp);
}
