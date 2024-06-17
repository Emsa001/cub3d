/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:51 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/17 18:54:45 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*check_map(char **map, int size)
{
	t_map	*map_info;

	map_info = ft_malloc(sizeof(t_map));
	map_info->width = 0;
	map_info->height = 0;
	map_info->no = NULL;
	map_info->so = NULL;
	map_info->we = NULL;
	map_info->ea = NULL;
	map_info->player_x = -1;
	map_info->player_y = -1;
	map_info->player_a = -1;
	map_info->map = NULL;
	get_no_so_we_ea(map_info, map);
	map_info->f = get_color(map_info, map, 'F');
	map_info->c = get_color(map_info, map, 'C');
	get_2d_map(map_info, map, size);
	get_map_sizes(map_info, map_info->map);
	get_player_position(map_info, map_info->map);
	check_valid(map_info->map, map_info);
	return (map_info);
}
