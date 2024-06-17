/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:10:09 by escura            #+#    #+#             */
/*   Updated: 2024/06/17 15:55:42 by btvildia         ###   ########.fr       */
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

	if (!av)
	{
		printf(GREEN "Usage: ./cub3d " BLUE "map.cub\n" RESET);
		exit(1);
	}
	c = ft_strjoin("src/maps/", av);
	fd = open(c, O_RDONLY);
	free(c);
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
	ft_free_arr(map);
	return (map_info);
}

t_cube	*init_cube(t_cube *c)
{
	static t_cube	*cube;

	if (c == NULL)
		return (cube);
	cube = c;
	return (cube);
}

t_cube	*cube(void)
{
	return (init_cube(NULL));
}
void	get_params(char *av)
{
	t_cube	*c;

	c = cube();
	c->map = get_map(av);
	c->mlx = mlx_init();
	c->keycode = D;
}
