/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:05:17 by escura            #+#    #+#             */
/*   Updated: 2024/08/23 21:36:04 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "textures.h"

static void init_hudtextures(t_textures *t){
	t_texture *healthhud = ft_malloc(sizeof(t_texture));
	healthhud->image = get_texture_file("assets/hud/Health_01.xpm", &healthhud->width, &healthhud->height);
	healthhud->data = mlx_get_data_addr(healthhud->image, &healthhud->bpp, &healthhud->size_line, &healthhud->endian);
	t->healthhud = healthhud;

	t_texture *healthbar = ft_malloc(sizeof(t_texture));
	healthbar->image = get_texture_file("assets/hud/Health_01_Bar01.xpm", &healthbar->width, &healthbar->height);
	healthbar->data = mlx_get_data_addr(healthbar->image, &healthbar->bpp, &healthbar->size_line, &healthbar->endian);
	t->healthbar = healthbar;

	t_texture *healthIcon1 = ft_malloc(sizeof(t_texture));
	healthIcon1->image = get_texture_file("assets/hud/Heart_Red_1.xpm", &healthIcon1->width, &healthIcon1->height);
	healthIcon1->data = mlx_get_data_addr(healthIcon1->image, &healthIcon1->bpp, &healthIcon1->size_line, &healthIcon1->endian);
	t->healthIcon[0] = healthIcon1;

	t_texture *healthIcon2 = ft_malloc(sizeof(t_texture));
	healthIcon2->image = get_texture_file("assets/hud/Heart_Red_2.xpm", &healthIcon2->width, &healthIcon2->height);
	healthIcon2->data = mlx_get_data_addr(healthIcon2->image, &healthIcon2->bpp, &healthIcon2->size_line, &healthIcon2->endian);
	t->healthIcon[1] = healthIcon2;

	t_texture *healthIcon3 = ft_malloc(sizeof(t_texture));
	healthIcon3->image = get_texture_file("assets/hud/Heart_Red_3.xpm", &healthIcon3->width, &healthIcon3->height);
	healthIcon3->data = mlx_get_data_addr(healthIcon3->image, &healthIcon3->bpp, &healthIcon3->size_line, &healthIcon3->endian);
	t->healthIcon[2] = healthIcon3;

	t_texture *healthIcon4 = ft_malloc(sizeof(t_texture));
	healthIcon4->image = get_texture_file("assets/hud/Heart_Red_4.xpm", &healthIcon4->width, &healthIcon4->height);
	healthIcon4->data = mlx_get_data_addr(healthIcon4->image, &healthIcon4->bpp, &healthIcon4->size_line, &healthIcon4->endian);
	t->healthIcon[3] = healthIcon4;
}

t_textures *init_textures(t_textures *t)
{
	static t_textures	*texture;
	void				*mlx = render()->mlx;

	if (t == NULL)
		return (texture);

	t_texture *player = ft_malloc(sizeof(t_texture));
	player->image = get_texture_file("assets/player.xpm", &player->width, &player->height);
	player->data = mlx_get_data_addr(player->image, &player->bpp, &player->size_line, &player->endian);
	t->player = player;

	t_texture *sky = ft_malloc(sizeof(t_texture));
	t_texture *floor = ft_malloc(sizeof(t_texture));

	sky->image = get_texture_file("assets/sky.xpm", &sky->width, &sky->height);
	sky->data = mlx_get_data_addr(sky->image, &sky->bpp, &sky->size_line, &sky->endian);
	t->sky = sky;

	floor->image = get_texture_file("assets/floor2.xpm", &floor->width, &floor->height);
	floor->data = mlx_get_data_addr(floor->image, &floor->bpp, &floor->size_line, &floor->endian);
	t->floor = floor;

	t_texture *door = ft_malloc(sizeof(t_texture));
	t_texture *wall_north = ft_malloc(sizeof(t_texture));
	t_texture *wall_south = ft_malloc(sizeof(t_texture));
	t_texture *wall_east = ft_malloc(sizeof(t_texture));
	t_texture *wall_west = ft_malloc(sizeof(t_texture));

	wall_north->image = get_texture_file("assets/north.xpm", &wall_north->width, &wall_north->height);
	wall_north->data = mlx_get_data_addr(wall_north->image, &wall_north->bpp, &wall_north->size_line, &wall_north->endian);
	t->wall_north = wall_north;
	
	wall_south->image = get_texture_file("assets/south.xpm", &wall_south->width, &wall_south->height);
	wall_south->data = mlx_get_data_addr(wall_south->image, &wall_south->bpp, &wall_south->size_line, &wall_south->endian);
	t->wall_south = wall_south;

	wall_east->image = get_texture_file("assets/east.xpm", &wall_east->width, &wall_east->height);
	wall_east->data = mlx_get_data_addr(wall_east->image, &wall_east->bpp, &wall_east->size_line, &wall_east->endian);
	t->wall_east = wall_east;

	wall_west->image = get_texture_file("assets/west.xpm", &wall_west->width, &wall_west->height);
	wall_west->data = mlx_get_data_addr(wall_west->image, &wall_west->bpp, &wall_west->size_line, &wall_west->endian);
	t->wall_west = wall_west;
	
	door->image = get_texture_file("assets/door.xpm", &door->width, &door->height);
	door->data = mlx_get_data_addr(door->image, &door->bpp, &door->size_line, &door->endian);
	t->door = door;


	init_hudtextures(t);
	
	texture = t;
	return (texture);
}

t_textures *textures(void)
{
	return (init_textures(NULL));
}