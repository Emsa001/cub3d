/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:42:00 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/26 20:30:53 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	texture_error(t_textures *t)
{
	t_cube	*c;

	c = cube();
	if (t->wall_north)
		mlx_destroy_image(c->mlx, t->wall_north->image);
	if (t->wall_south)
		mlx_destroy_image(c->mlx, t->wall_south->image);
	if (t->wall_east)
		mlx_destroy_image(c->mlx, t->wall_east->image);
	if (t->wall_west)
		mlx_destroy_image(c->mlx, t->wall_west->image);
	mlx_destroy_display(c->mlx);
	free(c->mlx);
	ft_destructor();
	write(1, "Texture error\n", 15);
	exit(1);
}

t_texture	*load_texture(t_textures *tex, void *mlx, const char *path,
		char *real_path)
{
	t_texture	*t;
	int			width;
	int			height;

	if (!path)
		path = real_path;
	t = ft_malloc(sizeof(t_texture));
	t->image = mlx_xpm_file_to_image(mlx, (char *)path, &width, &height);
	if (t->image == NULL)
		texture_error(tex);
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
	t->wall_north = NULL;
	t->wall_south = NULL;
	t->wall_east = NULL;
	t->wall_west = NULL;
	t->wall_north = load_texture(t, mlx, c->map->no,
			"./assets/level1/north.xpm");
	t->wall_south = load_texture(t, mlx, c->map->so,
			"./assets/level1/south.xpm");
	t->wall_east = load_texture(t, mlx, c->map->ea, "./assets/level1/east.xpm");
	t->wall_west = load_texture(t, mlx, c->map->we, "./assets/level1/west.xpm");
	texture = t;
	return (texture);
}

t_textures	*textures(void)
{
	return (init_textures(NULL, NULL));
}
