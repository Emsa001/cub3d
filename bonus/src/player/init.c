/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:45:57 by escura            #+#    #+#             */
/*   Updated: 2024/09/13 14:24:38 by btvildia         ###   ########.fr       */
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

	player->jumping = false;
	player->jump_speed = 0;
	player->fall_speed = 0;

	player->interact = false;
	player->opened = false;
	player->spawn = false;
	player->remove = false;
	player->catch = false;
	player->catched = false;
	player->speed = WALKSPEED;
	player->sprint = false;
	player->pause = false;
	player->fov = FOV;

	player->mouse_hook = true;
	player->open_inventory = false;

	for(int i = 0; i < 9; i++)
		player->equipped[i] = -1;

	player->inventory[0] = 37;
	player->inventory[1] = 112;
	player->inventory[2] = 112;
	player->inventory[3] = 129;
	player->inventory[4] = 53;
	player->inventory[5] = 59;
	player->inventory[6] = 50;
	player->inventory[7] = 49;
	player->inventory[8] = 255;
	

	player->vision = false;
	player->hand = NULL;
	player->swing = false;

	// player->tooltip = NULL;
	player->hover = NULL;
	player->money = 1000000;
	player->store = init_store();

	pthread_mutex_init(&player->money_mutex, NULL);
	
	return (player);
}

t_player	*player(void)
{
	return (player_init(NULL));
}
