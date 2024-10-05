/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:20:57 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 16:13:17 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game()
{
	cube_init(ft_calloc(1,sizeof(t_cube)));
	init_render(ft_calloc(1,sizeof(t_render)));
	// map_init(map);

	player_init(ft_calloc(1,sizeof(t_player)));
	// init_textures(ft_calloc(1,sizeof(t_textures)));
	init_textures(ft_calloc(1,sizeof(t_textures)));
	// init_items();
	// minimap_init();
	cube()->render = render();
	cube()->player = player();
	cube()->textures = textures();
}

int	main()
{
	ft_alloc_init();
	init_game();
	start_game();
	return (0);
}
