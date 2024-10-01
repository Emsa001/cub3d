/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:24:21 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/01 12:35:33 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*get_info(char *path_file, int i)
{
	char		*path;
	char		*temp;
	t_texture	*tex;

	tex = ft_malloc(sizeof(t_texture));
	path = ft_strjoin(path_file, ft_itoa(i));
	temp = ft_strjoin(path, ".xpm");
	tex->image = get_texture_file(temp, &tex->width, &tex->height);
	tex->data = mlx_get_data_addr(tex->image, &tex->bpp, &tex->size_line,
			&tex->endian);
	ft_free(temp);
	ft_free(path);
	return (tex);
}

t_sprite	get_sprite(char *path_file, int frames, float x, float y)
{
	t_texture	**s_t;
	t_sprite	sprite;
	int			i;
	char		*path;
	char		*temp;

	s_t = ft_malloc(sizeof(t_texture) * frames);
	i = 0;
	while (i < frames)
	{
		s_t[i] = get_info(path_file, i);
		i++;
	}
	sprite.x = x;
	sprite.y = y;
	sprite.frames = frames;
	sprite.sprite_tex = s_t;
	sprite.width = s_t[0]->width;
	sprite.height = s_t[0]->height;
	sprite.type = '\0';
	if (frames == 5)
		sprite.type = 'P';
	return (sprite);
}

void	open_portal(int i)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	x = cube()->map->portals[i].x;
	y = cube()->map->portals[i].y;
	remove_sprite(x, y);
	add_sprite("assets/portal_opened/", 17, x, y);
}
