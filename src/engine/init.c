/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:10:09 by escura            #+#    #+#             */
/*   Updated: 2024/07/13 18:06:42 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* CUBE */

t_cube	*init_cube(t_cube *c)
{
	static t_cube	*cube;
	
	if (c == NULL)
		return (cube);

	c->mlx = mlx_init();
	c->keycode = D;
	
	t_render *r = ft_malloc(sizeof(t_render));
	r->mlx = c->mlx;
	init_render(r);

	t_textures *t = ft_malloc(sizeof(t_textures));
	init_textures(t, c->mlx);

	cube = c;
	return (cube);
}

t_cube	*cube(void)
{
	return (init_cube(NULL));
}

t_render *init_render(t_render *r)
{
	static t_render	*render;

	if (r == NULL)
		return (render);

	render = r;
	return (render);
}

t_render *render(void)
{
	return (init_render(NULL));
}

t_textures *init_textures(t_textures *t, void *mlx)
{
	static t_textures	*texture;

	if (t == NULL)
		return (texture);

	t_texture *sky = ft_malloc(sizeof(t_texture));
	t_texture *floor = ft_malloc(sizeof(t_texture));

	sky->image = mlx_xpm_file_to_image(mlx, "assets/sky.xpm", &sky->width, &sky->height);
	sky->data = mlx_get_data_addr(sky->image, &sky->bpp, &sky->size_line, &sky->endian);
	t->sky = sky;

	floor->image = mlx_xpm_file_to_image(mlx, "assets/floor.xpm", &floor->width, &floor->height);
	floor->data = mlx_get_data_addr(floor->image, &floor->bpp, &floor->size_line, &floor->endian);
	t->floor = floor;

	t_texture *wall_north = ft_malloc(sizeof(t_texture));
	t_texture *wall_south = ft_malloc(sizeof(t_texture));
	t_texture *wall_east = ft_malloc(sizeof(t_texture));
	t_texture *wall_west = ft_malloc(sizeof(t_texture));

	wall_north->image = mlx_xpm_file_to_image(mlx, "assets/wall2.xpm", &wall_north->width, &wall_north->height);
	wall_north->data = mlx_get_data_addr(wall_north->image, &wall_north->bpp, &wall_north->size_line, &wall_north->endian);
	t->wall_north = wall_north;
	

	texture = t;
	return (texture);
}

t_textures *textures(void)
{
	return (init_textures(NULL, NULL));
}