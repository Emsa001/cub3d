/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:05:17 by escura            #+#    #+#             */
/*   Updated: 2024/09/17 16:38:25 by escura           ###   ########.fr       */
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

t_texture **init_textures_array(char *path, void *mlx)
{
	t_texture **textures = ft_malloc(sizeof(t_texture *) * cube()->levels); 

	char *tmp;
	char *tmp2;
	int i = 0;
	while (i < cube()->levels)
	{
		tmp = ft_strjoin("assets/level", ft_itoa(i));
		tmp2 = ft_strjoin(tmp, "/");
		ft_free(tmp);
		tmp = ft_strjoin(tmp2, path);
		ft_free(tmp2);
		tmp2 = ft_strjoin(tmp, ".xpm");
		textures[i] = ft_malloc(sizeof(t_texture));
		textures[i]->image = get_texture_file(tmp2, &textures[i]->width, &textures[i]->height);
		textures[i]->data = mlx_get_data_addr(textures[i]->image, &textures[i]->bpp, &textures[i]->size_line, &textures[i]->endian);
		ft_free(tmp);
		ft_free(tmp2);
		i++;
	}
	return (textures);
}

t_texture *init_textures_level(char *path, void *mlx, int level_num)
{
	t_texture *textures = ft_malloc(sizeof(t_texture));

	char *tmp;
	char *tmp2;
	tmp = ft_strjoin("assets/level", "0");
	tmp2 = ft_strjoin(tmp, "/");
	ft_free(tmp);
	tmp = ft_strjoin(tmp2, path);
	ft_free(tmp2);
	tmp2 = ft_strjoin(tmp, ".xpm");
	
	textures->image = get_texture_file(tmp2, &textures->width, &textures->height);
	textures->data = mlx_get_data_addr(textures->image, &textures->bpp, &textures->size_line, &textures->endian);

	ft_free(tmp);
	ft_free(tmp2);
	return (textures);
}

t_textures *init_textures(t_textures *t)
{
	static t_textures	*texture;
	void				*mlx = render()->mlx;

	if (t == NULL)
		return (texture);

	cube()->levels = 3;

	t->ceiling = init_textures_array("ceiling", mlx);
	t->floor = init_textures_array("floor", mlx);
	t->wall_north = init_textures_array("north", mlx);
	t->wall_south = init_textures_array("south", mlx);
	t->wall_east = init_textures_array("east", mlx);
	t->wall_west = init_textures_array("west", mlx);
	
	t_texture *door = ft_malloc(sizeof(t_texture));
	t_texture *generator = ft_malloc(sizeof(t_texture));
	t_texture *generator1 = ft_malloc(sizeof(t_texture));
	t_texture *generator_top = ft_malloc(sizeof(t_texture));
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

	t_texture *open_portal = ft_calloc(1,sizeof(t_texture));
	open_portal->image = get_texture_file("assets/banners/portal.xpm", &open_portal->width, &open_portal->height);
	open_portal->data = mlx_get_data_addr(open_portal->image, &open_portal->bpp, &open_portal->size_line, &open_portal->endian);
	t->open_portal = open_portal;
	
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