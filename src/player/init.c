/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:45:57 by escura            #+#    #+#             */
/*   Updated: 2024/06/18 19:00:06 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* PLAYER */

t_player	*init_player(t_player *p)
{
	static t_player	*player;

	if (p == NULL)
		return (player);
	player = p;

    player->x = -1;
	player->y = -1;
	player->a = -1;
    get_player_position(cube()->map->map);

	return (player);
}

t_player	*player(void)
{
	return (init_player(NULL));
}
