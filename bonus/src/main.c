/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:20:57 by escura            #+#    #+#             */
/*   Updated: 2024/07/16 13:43:37 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_game(char *map)
{
	init_cube(ft_malloc(sizeof(t_cube)));
	init_map(map);
	init_player(ft_malloc(sizeof(t_player)));
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
