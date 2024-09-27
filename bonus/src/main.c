/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:20:57 by escura            #+#    #+#             */
/*   Updated: 2024/09/27 18:43:33 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game(char *map)
{
	// if (!XInitThreads()) {
	//     printf("Failed to initialize X11 threading support\n");
	//     exit(1);
	// }
	cube_init(ft_calloc(1,sizeof(t_cube)));
	init_render(ft_calloc(1,sizeof(t_render)));
	map_init(map);
	player_init(ft_calloc(1,sizeof(t_player)));
	init_textures(ft_calloc(1,sizeof(t_textures)));
	init_items();
	minimap_init();
	cube()->render = render();
	cube()->player = player();
	cube()->textures = textures();
}

int	main(int argc, char **argv)
{
	check_params(argv);
	ft_alloc_init();
	init_game(argv[1]);
	sleep(1);
	start_game();
	return (0);
}
