/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:51 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/23 17:47:45 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_c(char **map, char c)
{
	int	i;
	int	j;
	int	zero;

	i = 0;
	j = 0;
	zero = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == c)
				zero++;
			j++;
		}
		i++;
	}
	return (zero);
}

void	check_valid(char **map, t_map *map_info)
{
	t_point	size;
	t_point	*begin_points;
	char	to_fill[9];

	begin_points = ft_malloc(sizeof(t_point) * (count_c(map, '0') + 1));
	begin_points = get_begin_points(map, begin_points);
	begin_points[count_c(map, '0')].x = -1;
	begin_points[count_c(map, '0')].y = -1;
	to_fill[0] = '0';
	to_fill[1] = 'N';
	to_fill[2] = 'S';
	to_fill[3] = 'W';
	to_fill[4] = 'E';
	to_fill[5] = 'D';
	to_fill[6] = 'G';
	to_fill[7] = 'P';
	to_fill[8] = 'M';
	size.x = map_info->width + 1;
	size.y = map_info->height;
	fill_loop(to_fill, begin_points, map_info, size);
	ft_free(begin_points);
}

int	count_lines(char **map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map[i] != NULL)
	{
		if (ft_strncmp(map[i], "Line", 4) == 0)
			count++;
		i++;
	}
	return (count);
}

float	ft_float_atoi(char *str)
{
	float	res;
	float	dec;
	int		i;
	int		j;
	int		sign;

	i = 0;
	j = 0;
	sign = 1;
	res = 0;
	dec = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != '.' && str[i] != '\0' && str[i] != '\n')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] != '\0' && str[i] != '\n')
		{
			dec = dec * 10 + str[i] - '0';
			i++;
			j++;
		}
	}
	while (j > 0)
	{
		dec = dec / 10;
		j--;
	}
	return (sign * (res + dec));
}

t_block	get_line(char *line)
{
	t_block	block_line;
	char	**line_split;
	int		i;

	line_split = ft_split(line, ',');
	i = 0;
	block_line.s_x = ft_float_atoi(line_split[0]);
	block_line.s_y = ft_float_atoi(line_split[1]);
	block_line.x = ft_float_atoi(line_split[2]);
	block_line.y = ft_float_atoi(line_split[3]);
	while (line_split[i] != NULL)
	{
		ft_free(line_split[i]);
		i++;
	}
	ft_free(line_split);
	return (block_line);
}


t_block	*init_generators(t_map *map_info, char **map)
{
	t_block	*generators;
	int		i;
	int		j;
	int		k;
	int		generator_count;

	i = 0;
	j = 0;
	k = 0;
	map_info->generators = NULL;
	generator_count = count_c(map, 'G');
	generators = ft_malloc(sizeof(t_block) * (generator_count + 1));
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'G')
			{
				generators[k].x = j + 0.5;
				generators[k].y = i + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
	generators[k].x = -1;
	generators[k].y = -1;
	return (generators);
}

t_block	*init_map_block(t_map *map_info)
{
	t_block	*blocks;
	int		k;

	map_info->blocks = NULL;
	blocks = ft_calloc(sizeof(t_block), MAX_BLOCK + 1);
	k = 0;
	blocks[k].x = -1;
	blocks[k].y = -1;
	blocks[k].id = -1;
	blocks[k].s_x = -1;
	blocks[k].s_y = -1;
	blocks[k].type = '\0';
	return (blocks);
}

t_point	*get_points(char **map, char c)
{
	int		k;
	int		count;
	t_point	*points;
	int		i;
	int		j;

	k = 0;
	count = count_c(map, c);
	points = ft_malloc(sizeof(t_point) * (count + 1));
	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == c)
			{
				points[k].x = j;
				points[k].y = i;
				k = k + 1;
			}
			j++;
		}
		i++;
	}
	points[k].x = -1;
	points[k].y = -1;
	return (points);
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

t_sprite	get_sprite(char *path_file, int frames, float x, float y)
{
	t_texture	**sprite_texture;
	t_sprite	sprite;
	int			i;
	char		*path;
	char		*temp;

	sprite_texture = ft_malloc(sizeof(t_texture) * frames);
	i = 0;
	while (i < frames)
	{
		sprite_texture[i] = ft_malloc(sizeof(t_texture));
		path = ft_strjoin(path_file, ft_itoa(i));
		temp = ft_strjoin(path, ".xpm");
		sprite_texture[i]->image = get_texture_file(temp,
				&sprite_texture[i]->width, &sprite_texture[i]->height);
		sprite_texture[i]->data = mlx_get_data_addr(sprite_texture[i]->image,
				&sprite_texture[i]->bpp, &sprite_texture[i]->size_line,
				&sprite_texture[i]->endian);
		ft_free(temp);
		ft_free(path);
		i++;
	}
	sprite.x = x;
	sprite.y = y;
	sprite.frames = frames;
	sprite.sprite_tex = sprite_texture;
	sprite.width = sprite_texture[0]->width;
	sprite.height = sprite_texture[0]->height;
	sprite.type = '\0';
	if (frames == 5)
		sprite.type = 'P';
	return (sprite);
}

t_sprite	*init_map_sprites(t_map *map_info, char **map)
{
	t_sprite	*sprites;
	int			i;
	int			j;
	int			k;
	t_point		*p_points;
	int			p_count;
	t_point		*m_points;
	int			m_count;

	sprites = ft_malloc(sizeof(t_sprite));
	k = 0;
	p_points = get_points(map, 'P');
	p_count = count_c(map, 'P');
	m_points = get_points(map, 'M');
	m_count = count_c(map, 'M');
	sprites = ft_malloc(sizeof(t_sprite) * (p_count + m_count + 1));
	i = 0;
	while (p_points[i].x != -1)
	{
		sprites[k] = get_sprite("assets/portal_closed/", 5, p_points[i].x,
				p_points[i].y);
		k++;
		i++;
	}
	i = 0;
	while (m_points[i].x != -1)
	{
		sprites[k] = get_sprite("assets/shop/", 28, m_points[i].x,
				m_points[i].y);
		k++;
		i++;
	}
	sprites[k].x = -1;
	sprites[k].y = -1;
	sprites[k].frames = -1;
	sprites[k].sprite_tex = NULL;
	sprites[k].width = -1;
	sprites[k].height = -1;
	sprites[k].type = '\0';
	return (sprites);
}

t_sprite	*init_map_facing(char **map)
{
	t_sprite	*sprites;
	int			i;
	int			j;
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
	return (sprites);
}

t_map	*check_map(char **map, int size)
{
	t_map	*map_info;

	map_info = ft_malloc(sizeof(t_map));
	map_info->width = 0;
	map_info->height = 0;
	map_info->sprite_count = 0;
	map_info->portal = false;
	map_info->map = NULL;
	map_info->lines = NULL;
	map_info->sprites = NULL;
	map_info->facing = NULL;
	get_2d_map(map_info, map, size);
	get_map_sizes(map_info, map_info->map);
	check_valid(map_info->map, map_info);
	map_info->doors = init_block(map_info, 'D');
	map_info->lines = init_map_block(map_info);
	map_info->blocks = init_map_block(map_info);
	map_info->generators = init_generators(map_info, map);
	map_info->facing = init_map_facing(map);
	map_info->sprites = init_map_sprites(map_info, map);
	map_info->sprite_count = (count_c(map, 'P') + count_c(map, 'M')) * 64;
	map_info->portals = get_points(map, 'P');
	map_info->editor_mode = false;
	return (map_info);
}
