/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:45:57 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 02:27:59 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* PLAYER */

static void	init_inventory(t_player *player)
{
	int	i;

	player->inventory[0] = 33;
	player->inventory[1] = 33;
	player->inventory[2] = 33;
	player->inventory[3] = 33;
	player->inventory[4] = 33;
	player->inventory[5] = 33;
	player->inventory[6] = 33;
	player->inventory[7] = 33;
	player->inventory[8] = 33;
	i = 0;
	while (i < 9)
		player->equipped[i++] = -1;
}

static void	init_interaction(t_player *player)
{
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
	player->mouse_hook = true;
}

static void	init_options(t_player *player)
{
	player->level = 0;
	player->hand = NULL;
	player->swing = false;
	player->hover = NULL;
	player->money = 10000000;
	player->store = init_store();
	player->GUI = -1;
	player->GUI_temp = -1;
	player->generator = NULL;
	player->math_selected = -1;
	player->streak = 0;
}

t_player	*player_init(t_player *p)
{
	static t_player	*player;

	if (p == NULL)
		return (player);
	player = p;
	get_player_position(cube()->map->map);
	init_interaction(player);
	init_inventory(player);
	init_options(player);
	player->x_px = player->x * BLOCK_SIZE;
	player->y_px = player->y * BLOCK_SIZE;
	player->z = 0.5;
	player->x_dir = 0;
	player->y_dir = 0;
	player->z_dir = 0.5;
	player->speed = WALKSPEED;
	player->sprint = false;
	player->pause = false;
	player->fov = FOV;
	pthread_mutex_init(&player->money_mutex, NULL);
	return (player);
}

t_player	*player(void)
{
	return (player_init(NULL));
}
