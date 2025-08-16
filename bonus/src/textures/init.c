/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:05:17 by escura            #+#    #+#             */
/*   Updated: 2024/10/07 15:28:13 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "textures.h"

t_texture	**init_textures_array(char *path, void *mlx)
{
	t_texture	**textures;
	int			i;
	char		*p;

	textures = ft_malloc(sizeof(t_texture *) * cube()->levels);
	i = 0;
	while (i < cube()->levels)
	{
		p = get_path(path, i);
		textures[i] = ft_malloc(sizeof(t_texture));
		textures[i]->image = get_texture_file(p, &textures[i]->width,
				&textures[i]->height);
		textures[i]->data = mlx_get_data_addr(textures[i]->image,
				&textures[i]->bpp, &textures[i]->size_line,
				&textures[i]->endian);
		ft_free(p);
		i++;
	}
	(void)mlx;
	return (textures);
}

static void	init_font(t_textures *t)
{
	int	index;
	int	src_x;
	int	src_y;
	int	i;
	int	j;

	t->font = load_texture("assets/font.xpm");
	index = 0;
	while (index < 95)
	{
		src_x = index % CHARS_PER_ROW * CHAR_WIDTH;
		src_y = index / CHARS_PER_ROW * CHAR_HEIGHT;
		i = 0;
		while (i < CHAR_WIDTH)
		{
			j = 0;
			while (++j < CHAR_HEIGHT)
				t->char_pixel_data[index][i + j
					* CHAR_WIDTH] = get_pixel_from_image(t->font, src_x + i,
						src_y + j);
			i++;
		}
		index++;
	}
}

static void	init_textures_to_null(t_textures *textures)
{
	int	i;

	i = 0;
	while (i < 2)
		textures->generator[i++] = NULL;
	textures->ui = ft_calloc(1, sizeof(t_uitextures));
	i = 0;
	while (i < 328)
		textures->items[i++] = (t_texture){0};
	i = 0;
	while (i < 32)
		textures->ui->keys[i++] = (t_texture){0};
	i = 0;
	while (i < 24)
		textures->ui->progress[i++] = (t_texture){0};
	i = 0;
	while (i < 3)
		textures->ui->progress_cover[i++] = (t_texture){0};
	i = 0;
	while (i < 8)
		textures->ui->loading[i++] = (t_texture){0};
	i = 0;
}

t_textures	*init_textures(t_textures *t)
{
	static t_textures	*texture;
	void *const			mlx = render()->mlx;

	if (t == NULL)
		return (texture);
	texture = t;
	init_textures_to_null(texture);
	texture->ceiling = init_textures_array("ceiling", mlx);
	texture->floor = init_textures_array("floor", mlx);
	texture->wall_north = init_textures_array("north", mlx);
	texture->wall_south = init_textures_array("south", mlx);
	texture->wall_east = init_textures_array("east", mlx);
	texture->wall_west = init_textures_array("west", mlx);
	texture->door = load_texture("assets/level3/door.xpm");
	texture->generator[0] = load_texture("assets/generator0.xpm");
	texture->generator[1] = load_texture("assets/generator1.xpm");
	texture->generator_top = load_texture("assets/back.xpm");
	texture->open_portal = load_texture("assets/banners/portal.xpm");
	texture->tooltip_bg = load_texture("assets/hud/titlebox.xpm");
	texture->inventory_player = load_texture("assets/hud/inventory.xpm");
	texture->inventory_gui = load_texture("assets/hud/inventory_gui.xpm");
	init_font(texture);
	init_items_textures(texture);
	init_ui(texture);
	return (texture);
}

t_textures	*textures(void)
{
	return (init_textures(NULL));
}
