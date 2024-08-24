/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:19:15 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 19:44:29 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// 

void init_map(char *av)
{
	char **map;
	int i;
	int fd;
	char *c;
	t_map *map_info;

	c = ft_strjoin("./maps/", av);
	fd = open(c, O_RDONLY);
	ft_free(c);
	if (fd == -1)
		ft_error("Map not found");
	map = ft_malloc(sizeof(char *) * MAX_SIZE);
	i = 0;
	while (1)
	{
		if (i >= MAX_SIZE)
			ft_error("Map too big");
		map[i] = get_next_line(fd);
		if (!map[i])
			break;
		i++;
	}
	map[i] = NULL;
	close(fd);
	map_info = check_map(map, i);
	ft_arrdel((void **)map);
	cube()->map = map_info;
}