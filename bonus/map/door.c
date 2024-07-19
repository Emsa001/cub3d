/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:41 by btvildia          #+#    #+#             */
/*   Updated: 2024/07/19 16:47:07 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int block_count(t_map *map_info, char c)
{
    int i;
    int j;
    int count;

    i = 0;
    j = 0;
    count = 0;

    if(c == '2')
    {
        if(map_info->blocks == NULL)
            return (0);
        while(map_info->blocks[count].x != -1)
            count++;
    }
    else
    {
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
    }
    return (count);
}

t_block    *init_block(t_map *map_info , char c)
{
    t_block    *blocks;
    int        i;
    int        j;
    int        k;
    
    map_info->blocks = NULL;
    int count = block_count(map_info, c);
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
                blocks[k].save_x = j;
                blocks[k].save_y = i;
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
    blocks[k].id = -1;
    blocks[k].save_x = -1;
    blocks[k].save_y = -1;
    blocks[k].type = '\0';
    return (blocks);
}
