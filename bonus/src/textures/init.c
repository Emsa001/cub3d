/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:05:17 by escura            #+#    #+#             */
/*   Updated: 2024/09/08 16:44:12 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "textures.h"

static void init_font(t_textures *t){
	t_texture *font = ft_malloc(sizeof(t_texture));
	font->image = get_texture_file("assets/font.xpm", &font->width, &font->height);
	font->data = mlx_get_data_addr(font->image, &font->bpp, &font->size_line, &font->endian);
	t->font = font;
}

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


	t_texture *inventoryPlayer = ft_malloc(sizeof(t_texture));
	inventoryPlayer->image = get_texture_file("assets/hud/inventory.xpm", &inventoryPlayer->width, &inventoryPlayer->height);
	inventoryPlayer->data = mlx_get_data_addr(inventoryPlayer->image, &inventoryPlayer->bpp, &inventoryPlayer->size_line, &inventoryPlayer->endian);
	t->inventoryPlayer = inventoryPlayer;

	t_texture *inventoryGui = ft_malloc(sizeof(t_texture));
	inventoryGui->image = get_texture_file("assets/hud/inventory_gui.xpm", &inventoryGui->width, &inventoryGui->height);
	inventoryGui->data = mlx_get_data_addr(inventoryGui->image, &inventoryGui->bpp, &inventoryGui->size_line, &inventoryGui->endian);
	t->inventoryGui = inventoryGui;
}

void init_tooltip(t_textures *t){
	t_texture *tooltip_bg = ft_malloc(sizeof(t_texture));
	tooltip_bg->image = get_texture_file("assets/hud/titlebox.xpm", &tooltip_bg->width, &tooltip_bg->height);
	tooltip_bg->data = mlx_get_data_addr(tooltip_bg->image, &tooltip_bg->bpp, &tooltip_bg->size_line, &tooltip_bg->endian);
	t->tooltip_bg = tooltip_bg;
}

static void init_torch(t_textures *t)
{
	// 9 steands for 9 frames of the torch animation
	t_texture *torch[9];
	int i = 0;

	while (i < 9)
	{
		torch[i] = ft_malloc(sizeof(t_texture));
		char *path = ft_strjoin("assets/torch/", ft_itoa(i));
		path = ft_strjoin(path, ".xpm");
		torch[i]->image = get_texture_file(path, &torch[i]->width, &torch[i]->height);
		torch[i]->data = mlx_get_data_addr(torch[i]->image, &torch[i]->bpp, &torch[i]->size_line, &torch[i]->endian);
		t->torch[i] = torch[i];
		i++;
	}
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

	floor->image = get_texture_file("assets/floor.xpm", &floor->width, &floor->height);
	floor->data = mlx_get_data_addr(floor->image, &floor->bpp, &floor->size_line, &floor->endian);
	t->floor = floor;

	t_texture *door = ft_malloc(sizeof(t_texture));
	t_texture *wall_north = ft_malloc(sizeof(t_texture));
	t_texture *wall_south = ft_malloc(sizeof(t_texture));
	t_texture *wall_east = ft_malloc(sizeof(t_texture));
	t_texture *wall_west = ft_malloc(sizeof(t_texture));
	t_texture *chest = ft_malloc(sizeof(t_texture));
	t_texture *chest_top = ft_malloc(sizeof(t_texture));

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

	chest->image = get_texture_file("assets/chest.xpm", &chest->width, &chest->height);
	chest->data = mlx_get_data_addr(chest->image, &chest->bpp, &chest->size_line, &chest->endian);
	t->chest = chest;

	chest_top->image = get_texture_file("assets/chest_top.xpm", &chest_top->width, &chest_top->height);
	chest_top->data = mlx_get_data_addr(chest_top->image, &chest_top->bpp, &chest_top->size_line, &chest_top->endian);
	t->chest_top = chest_top;

	init_torch(t);
	init_hudtextures(t);
	init_items_textures(t);
	init_font(t);
	init_tooltip(t);
	
	texture = t;
	return (texture);
}

t_textures *textures(void)
{
	return (init_textures(NULL));
}