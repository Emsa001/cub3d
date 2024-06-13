/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:59:54 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/13 21:15:11 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_map_info(t_map *map)
{
	int i = 0;
	printf(GREEN"width: "BLUE"%d\n", map->width);
	printf(GREEN"height: "BLUE"%d\n", map->height);
	printf(GREEN"NO: "BLUE"%s"RESET, map->no);
	printf(GREEN"SO: "BLUE"%s"RESET, map->so);
	printf(GREEN"WE: "BLUE"%s"RESET, map->we);
	printf(GREEN"EA: "BLUE"%s"RESET, map->ea);
	printf(GREEN"F: "BLUE" %d, %d, %d\n"RESET, map->f[0], map->f[1], map->f[2]);
	printf(GREEN"C: "BLUE" %d, %d, %d\n"RESET, map->c[0], map->c[1], map->c[2]);
	printf(GREEN"player_x: "BLUE"%f\n"RESET, map->player_x);
	printf(GREEN"player_y: "BLUE"%f\n"RESET, map->player_y);
	printf(GREEN"player_a: "BLUE"%f\n"RESET, map->player_a);
	while (i < map->height)
	{
		if(ft_strchr(map->map[i], 'N') || ft_strchr(map->map[i], 'S') || ft_strchr(map->map[i], 'W') || ft_strchr(map->map[i], 'E'))
			printf(GREEN"%s"RESET, map->map[i]);
		else
			printf("%s", map->map[i]);
		i++;
	}
	printf("\n");
}

void	ft_error(char *str)
{
    write(2, "Error\n", 6);
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    exit(1);
}

void ft_free_arr(char **array)
{
    int i = 0;
    while (array[i] != NULL) 
    {
        free(array[i]);
        i++;
    }
    free(array);
}
