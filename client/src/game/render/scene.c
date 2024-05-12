/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:56:26 by escura            #+#    #+#             */
/*   Updated: 2024/05/12 21:18:03 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int render_rect(t_data data, t_rect rect)
{
    if (data.win == NULL)
        return (1);

    // Draw top and bottom borders
    for (int j = rect.x; j < rect.x + rect.width; j++)
    {
        mlx_pixel_put(data.mlx, data.win, j, rect.y, rect.color);
        mlx_pixel_put(data.mlx, data.win, j, rect.y + rect.height, rect.color);
    }

    // Draw left and right borders
    for (int i = rect.y; i < rect.y + rect.height; i++)
    {
        mlx_pixel_put(data.mlx, data.win, rect.x, i, rect.color);
        mlx_pixel_put(data.mlx, data.win, rect.x + rect.width, i, rect.color);
    }

    return (0);
}

void	render_scene(t_data data)
{
    char *row, *map_copy;
    int i, j;

    mlx_clear_window(data.mlx, data.win);

    map_copy = ft_strdup(data.map);
    row = ft_strtok(map_copy, ",");

    for(i = 0; row != NULL; i++) {
        for(j = 0; j < ft_strlen(row); j++) {
            if(row[j] == 'E') {
                render_rect(data, (t_rect){j*data.block_size, i*data.block_size, data.block_size, data.block_size, 0x00f59e0b});
            }
            else if(row[j] == 'P') {
                render_rect(data, (t_rect){j*data.block_size, i*data.block_size, data.block_size, data.block_size, 0x00e7490});
            }
            else if(row[j] == 'G') {
                render_rect(data, (t_rect){j*data.block_size, i*data.block_size, data.block_size, data.block_size, 0x003730a3});
            }
            else if(row[j] == '1'){
                render_rect(data, (t_rect){j*data.block_size, i*data.block_size, data.block_size, data.block_size, 0x0044403c});
            }
        }
        row = ft_strtok(NULL, ",");
    }

    free(map_copy);
}