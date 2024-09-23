/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:42:00 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/23 14:42:58 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_texture	*load_texture(void *mlx, const char *path, int i)
{
	t_texture	*t;
	int			width;
	int			height;

	if (!path)
	{
		if (i == 0)
			path = ft_strdup("./assets/level1/north.xpm");
		else if (i == 1)
			path = ft_strdup("./assets/level1/south.xpm");
		else if (i == 2)
			path = ft_strdup("./assets/level1/east.xpm");
		else if (i == 3)
			path = ft_strdup("./assets/level1/west.xpm");
	}
	t = ft_malloc(sizeof(t_texture));
	t->image = mlx_xpm_file_to_image(mlx, (char *)path, &width, &height);
	if (t->image == NULL)
		ft_error("Invalid texture path");
	t->data = mlx_get_data_addr(t->image, &t->bpp, &t->size_line, &t->endian);
	t->width = width;
	t->height = height;
	return (t);
}

t_textures	*init_textures(t_textures *t, void *mlx)
{
	static t_textures	*texture;
	t_cube				*c;

	c = cube();
	if (t == NULL)
		return (texture);
	t->wall_north = load_texture(mlx, c->map->no, 0);
	t->wall_south = load_texture(mlx, c->map->so, 1);
	t->wall_east = load_texture(mlx, c->map->ea, 2);
	t->wall_west = load_texture(mlx, c->map->we, 3);
	texture = t;
	return (texture);
}

t_textures	*textures(void)
{
	return (init_textures(NULL, NULL));
}
