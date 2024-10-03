/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:05:17 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 18:50:59 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "textures.h"

static char	*get_path(char *path, int i)
{
	char	*num;
	char	*tmp;
	char	*tmp2;

	num = ft_itoa(i);
	tmp = ft_strjoin("assets/level", num);
	ft_free(num);
	tmp2 = ft_strjoin(tmp, "/");
	ft_free(tmp);
	tmp = ft_strjoin(tmp2, path);
	ft_free(tmp2);
	tmp2 = ft_strjoin(tmp, ".xpm");
	ft_free(tmp);
	return (tmp2);
}

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

t_textures	*init_textures(t_textures *t)
{
	static t_textures	*texture;
	void				*mlx;

	if (t == NULL)
		return (texture);
	mlx = render()->mlx;
	t->ceiling = init_textures_array("ceiling", mlx);
	t->floor = init_textures_array("floor", mlx);
	t->wall_north = init_textures_array("north", mlx);
	t->wall_south = init_textures_array("south", mlx);
	t->wall_east = init_textures_array("east", mlx);
	t->wall_west = init_textures_array("west", mlx);
	t->door = load_texture("assets/level3/door.xpm");
	t->generator = load_texture("assets/generator0.xpm");
	t->generator1 = load_texture("assets/generator1.xpm");
	t->generator_top = load_texture("assets/back.xpm");
	t->open_portal = load_texture("assets/banners/portal.xpm");
	t->tooltip_bg = load_texture("assets/hud/titlebox.xpm");
	t->inventory_player = load_texture("assets/hud/inventory.xpm");
	t->inventory_gui = load_texture("assets/hud/inventory_gui.xpm");
	init_font(t);
	init_items_textures(t);
	init_ui(t);
	texture = t;
	return (texture);
}

t_textures	*textures(void)
{
	return (init_textures(NULL));
}
