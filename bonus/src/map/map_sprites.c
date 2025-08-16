/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:24:21 by btvildia          #+#    #+#             */
/*   Updated: 2025/08/16 14:35:09 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_max_objects(char **map)
{
	if (count_c(map, 'N') != 1)
		ft_error("Error\nThere must be only one player");
	if (count_c(map, 'P') > 3)
		ft_error("Error\nThere must be at most 3 portals");
	if (count_c(map, 'M') > 20)
		ft_error("Error\nThere must be at most 20 shops");
	if (count_c(map, 'G') > 20)
		ft_error("Error\nThere must be at most 20 generators");
	if (count_c(map, 'D') > 20)
		ft_error("Error\nThere must be at most 20 doors");
}

t_texture	*get_info(char *path_file, int i)
{
	char *const			temp = ft_strjoin_itoa(path_file, i);
	char *const			path = ft_strjoin(temp, ".xpm");
	t_texture *const	t = load_texture(path);

	ft_free(temp);
	ft_free(path);
	return (t);
}

t_sprite	get_sprite(char *path_file, int frames, float x, float y)
{
	t_texture	**s_t;
	t_sprite	sprite;
	int			i;

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
	cube()->map->portals[i].open = true;
	add_sprite("assets/portal_opened/", 17, x, y);
}
