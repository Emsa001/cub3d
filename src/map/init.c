/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:19:15 by escura            #+#    #+#             */
/*   Updated: 2024/06/18 17:38:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_map	*get_map(char *av)
{
	char	**map;
	int		i;
	int		fd;
	char	*c;
	t_map	*map_info;

	c = ft_strjoin("./maps/", av);
	fd = open(c, O_RDONLY);
	ft_free(c);
	if (fd == -1)
		ft_error("Map not found");
	map = ft_malloc(sizeof(char *) * 100);
	i = 0;
	while (1)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
			break ;
		i++;
	}
	map[i] = NULL;
	close(fd);
	map_info = check_map(map, i);
	ft_arrdel((void **)map);
	return (map_info);
}

void	get_params(char **av)
{
	t_cube	*c;

	if (!av[1] || av[2])
	{
		printf(GREEN "Usage: ./cub3d " BLUE "map.cub\n" RESET);
		ft_exit();
	}

	t_player *p = ft_malloc(sizeof(t_player));
	init_player(p);
	
	cube()->map = get_map(av[1]);
	
}
