/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:33:00 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/03 19:33:11 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_shop(int *k, t_sprite **sprites, char **map)
{
	int		i;
	t_point	*points;

	points = ft_malloc(sizeof(t_point) * (count_c(map, 'M') + 1));
	get_points(&points, map, 'M');
	i = 0;
	while (points[i].x != -1)
	{
		(*sprites)[*k] = get_sprite("assets/shop/", 28, points[i].x,
				points[i].y);
		(*k)++;
		i++;
	}
}

void	init_portals(int *k, t_sprite **sprites, char **map)
{
	int		i;
	t_point	*points;

	points = ft_malloc(sizeof(t_point) * (count_c(map, 'P') + 1));
	get_points(&points, map, 'P');
	i = 0;
	while (points[i].x != -1)
	{
		(*sprites)[*k] = get_sprite("assets/portal_closed/", 5, points[i].x,
				points[i].y);
		(*k)++;
		i++;
	}
}

t_sprite	*init_map_sprites(t_map *map_info, char **map)
{
	t_sprite	*sprites;
	int			k;
	int			p_count;
	int			m_count;

	sprites = ft_malloc(sizeof(t_sprite));
	k = 0;
	p_count = count_c(map, 'P');
	m_count = count_c(map, 'M');
	sprites = ft_malloc(sizeof(t_sprite) * (p_count + m_count + 1));
	init_shop(&k, &sprites, map);
	init_portals(&k, &sprites, map);
	sprites[k].x = -1;
	sprites[k].y = -1;
	sprites[k].frames = -1;
	sprites[k].sprite_tex = NULL;
	sprites[k].width = -1;
	sprites[k].height = -1;
	sprites[k].type = '\0';
	(void)map_info;
	return (sprites);
}

t_sprite	*init_map_facing(char **map)
{
	t_sprite	*sprites;
	int			k;

	sprites = ft_malloc(sizeof(t_sprite));
	k = 0;
	sprites[k].x = -1;
	sprites[k].y = -1;
	sprites[k].frames = -1;
	sprites[k].sprite_tex = NULL;
	sprites[k].width = -1;
	sprites[k].height = -1;
	sprites[k].type = '\0';
	(void)map;
	return (sprites);
}
