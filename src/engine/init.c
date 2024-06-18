/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:10:09 by escura            #+#    #+#             */
/*   Updated: 2024/06/18 16:10:18 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*get_map(char *av)
{
	char	**map;
	int		i;
	int		fd;
	char	*c;
	t_map	*map_info;

	c = ft_strjoin("src/maps/", av);
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

t_cube	*init_cube(t_cube *c)
{
	static t_cube	*cube;

	if (c == NULL)
		return (cube);
	init_player(ft_malloc(sizeof(t_player)));
	cube = c;
	return (cube);
}

t_cube	*cube(void)
{
	return (init_cube(NULL));
}

t_player	*init_player(t_player *p)
{
	static t_player	*player;

	if (p == NULL)
		return (player);
	player = p;
	return (player);
}

t_player	*player(void)
{
	return (init_player(NULL));
}

void	get_params(char **av)
{
	t_cube	*c;

	if (!av[1] || av[2])
	{
		printf(GREEN "Usage: ./cub3d " BLUE "map.cub\n" RESET);
		ft_exit();
	}
	c = cube();
	c->map = get_map(av[1]);
	c->mlx = mlx_init();
	c->keycode = D;
}
