/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:45:57 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 13:51:06 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* PLAYER */

t_player	*player_init(t_player *p)
{
	static t_player	*player;

	if (p == NULL)
		return (player);
	player = p;

    get_player_position(cube()->map->map);
	
	player->x_px = player->x * BLOCK_SIZE;
	player->y_px = player->y * BLOCK_SIZE;
	player->z = 0.5;
	
	player->x_dir = 0;
	player->y_dir = 0;
	player->z_dir = 0.5;

	player->btn_w = false;
	player->btn_s = false;
	player->btn_a = false;
	player->btn_d = false;
	player->btn_left = false;
	player->btn_right = false;
	player->btn_up = false;
	player->btn_down = false;

	player->jump_height = JUMP_HEIGHT;

	player->interact = false;
	player->opened = false;
	player->spawn = false;
	player->remove = false;
	player->catch = false;
	player->catched = false;
	player->speed = WALKSPEED;
	player->pause = false;
	player->fov = FOV;

	player->health = 100;
	
	return (player);
}

t_player	*player(void)
{
	return (player_init(NULL));
}
