/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:20:57 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 21:41:32 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_game(char *map)
{
    if (!XInitThreads()) {
        printf("Failed to initialize X11 threading support\n");
        exit(1);
    }

	cube_init(ft_malloc(sizeof(t_cube)));
	init_render(ft_malloc(sizeof(t_render)));
	map_init(map);
	
	player_init(ft_malloc(sizeof(t_player)));
	init_textures(ft_malloc(sizeof(t_textures)));
	init_items();
	minimap_init();
}

int	main(int argc, char **argv)
{
	check_params(argv);
	ft_alloc_init();

	init_game(argv[1]);

	start_game();
	
	ft_destructor();
	return (0);
}
