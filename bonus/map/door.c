/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:41 by btvildia          #+#    #+#             */
/*   Updated: 2024/07/18 13:09:09 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    print_block_info(t_block *blocks)
{
    int i;

    i = 0;
    while (blocks[i].x != -1)
    {
        printf("Door %d: x = %f, y = %f\n", blocks[i].id, blocks[i].x, blocks[i].y);
        i++;
    }
}

int block_count(t_map *map_info, char c)
{
    int i;
    int j;
    int count;

    i = 0;
    j = 0;
    count = 0;
    while (map_info->map[i] != NULL)
    {
        j = 0;
        while (map_info->map[i][j] != '\0')
        {
            if (map_info->map[i][j] == c)
                count++;
            j++;
        }
        i++;
    }
    return (count);
}

t_block    *init_block(t_map *map_info , char c)
{
    t_block    *blocks;
    int        i;
    int        j;
    int        k;

    int count = block_count(map_info, c);
    if(count == 0)
        return (NULL);

    blocks = ft_malloc(sizeof(t_block) * (count + 1));
    i = 0;
    j = 0;
    k = 0;
    while (map_info->map[i] != NULL)
    {
        j = 0;
        while (map_info->map[i][j] != '\0')
        {
            if (map_info->map[i][j] == c)
            {
                blocks[k].x = j;
                blocks[k].y = i;
                blocks[k].z = 0;
                blocks[k].first_x = j;
                blocks[k].first_y = i;
                blocks[k].id = k;
                blocks[k].type = c;
                k++;
            }
            j++;
        }
        i++;
    }
    blocks[k].x = -1;
    blocks[k].y = -1;
    blocks[k].z = 0;
    blocks[k].id = -1;
    blocks[k].type = '\0';
    
    return (blocks);
}
