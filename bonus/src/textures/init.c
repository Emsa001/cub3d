/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:05:17 by escura            #+#    #+#             */
/*   Updated: 2024/09/13 20:16:16 by escura           ###   ########.fr       */
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
	t_texture *generator = ft_malloc(sizeof(t_texture));
	t_texture *generator1 = ft_malloc(sizeof(t_texture));
	t_texture *generator_top = ft_malloc(sizeof(t_texture));

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

	generator->image = get_texture_file("assets/generator0.xpm", &generator->width, &generator->height);
	generator->data = mlx_get_data_addr(generator->image, &generator->bpp, &generator->size_line, &generator->endian);
	t->generator = generator;
	
	generator1->image = get_texture_file("assets/generator1.xpm", &generator1->width, &generator1->height);
	generator1->data = mlx_get_data_addr(generator1->image, &generator1->bpp, &generator1->size_line, &generator1->endian);
	t->generator1 = generator1;

	generator_top->image = get_texture_file("assets/back.xpm", &generator_top->width, &generator_top->height);
	generator_top->data = mlx_get_data_addr(generator_top->image, &generator_top->bpp, &generator_top->size_line, &generator_top->endian);
	t->generator_top = generator_top;
	init_hudtextures(t);

	init_items_textures(t);
	init_font(t);
	init_tooltip(t);
	init_ui(t);
	
	texture = t;
	return (texture);
}

t_textures *textures(void)
{
	return (init_textures(NULL));
}