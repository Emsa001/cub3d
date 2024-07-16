/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:41 by btvildia          #+#    #+#             */
/*   Updated: 2024/07/16 20:56:46 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    print_door_info(t_door *doors)
{
    int i;

    i = 0;
    while (doors[i].x != -1)
    {
        printf("Door %d: x = %f, y = %f\n", doors[i].id, doors[i].x, doors[i].y);
        i++;
    }
}

int door_count(t_map *map_info)
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
            if (map_info->map[i][j] == 'D')
                count++;
            j++;
        }
        i++;
    }
    return (count);
}

t_door    *init_door(t_map *map_info)
{
    t_door    *doors;
    int        i;
    int        j;
    int        k;

    int count = door_count(map_info);
    if(count == 0)
        return (NULL);

    doors = ft_malloc(sizeof(t_door) * (count + 1));
    i = 0;
    j = 0;
    k = 0;
    while (map_info->map[i] != NULL)
    {
        j = 0;
        while (map_info->map[i][j] != '\0')
        {
            if (map_info->map[i][j] == 'D')
            {
                doors[k].x = j;
                doors[k].y = i;
                doors[k].z = 0;
                doors[k].first_x = j;
                doors[k].first_y = i;
                doors[k].id = k;
                k++;
            }
            j++;
        }
        i++;
    }
    doors[k].x = -1;
    doors[k].y = -1;
    doors[k].z = 0;
    doors[k].id = -1;
    
    return (doors);
}
