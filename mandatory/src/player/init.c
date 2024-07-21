/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:45:57 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 12:24:35 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* PLAYER */

static void player_hooks(t_player *player)
{
	player->btn_w = false;
	player->btn_s = false;
	player->btn_a = false;
	player->btn_d = false;
	player->btn_left = false;
	player->btn_right = false;
	player->btn_up = false;
	player->btn_down = false;
}

static void player_default(t_player *player){
	player->speed = WALKSPEED;
	player->fov = FOV;
}

t_player	*init_player(t_player *p)
{
	static t_player	*player;

	if (p == NULL)
		return (player);
	player = p;

    get_player_position(cube()->map->map);
	
	player->x_px = player->x * BLOCK_SIZE;
	player->y_px = player->y * BLOCK_SIZE;
	
	player->x_dir = 0;
	player->y_dir = 0;

	player_hooks(player);
	player_default(player);

	return (player);
}

t_player	*player(void)
{
	return (init_player(NULL));
}
