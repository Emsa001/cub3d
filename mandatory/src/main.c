/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:20:57 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 19:33:12 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// format must end .cub

static void check_format(char *map)
{
	int len;

	len = ft_strlen(map);
	if (len <= 4 || map[len - 1] != 'b' || map[len - 2] != 'u' || map[len - 3] != 'c' || map[len - 4] != '.')
		ft_error("Invalid map format");
}

static void init_game(char *map)
{
	check_format(map);
	init_cube(ft_malloc(sizeof(t_cube)));
	init_map(map);
	t_textures *t = ft_malloc(sizeof(t_textures));
	init_textures(t, cube()->mlx);
	init_player(ft_malloc(sizeof(t_player)));
}

int main(int argc, char **argv)
{
	check_params(argv);
	ft_alloc_init();
	init_game(argv[1]);
	start_game();

	ft_destructor();
	return (0);
}
