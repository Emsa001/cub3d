/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:51 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/19 14:01:55 by btvildia         ###   ########.fr       */
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
	char	to_fill[8];

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
	size.x = map_info->width + 1;
	size.y = map_info->height;
	fill_loop(to_fill, begin_points, map_info, size);
	ft_free(begin_points);
}

int count_lines(char **map)
{
	int i;
	int count;
	
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

float ft_float_atoi(char *str)
{
	float res;
	float dec;
	int i;
	int j;
	int sign;
	
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


t_block get_line(char *line)
{
	t_block block_line;
	char **line_split;
	
	line_split = ft_split(line, ',');

	int i = 0;
	
	block_line.s_x = ft_float_atoi(line_split[0]);
	block_line.s_y = ft_float_atoi(line_split[1]);
	block_line.x = ft_float_atoi(line_split[2]);
	block_line.y = ft_float_atoi(line_split[3]);
	
	while(line_split[i] != NULL)
	{
		ft_free(line_split[i]);
		i++;
	}
	ft_free(line_split);
	return (block_line);
}

t_block *init_line(t_map *map_info , char **map)
{
	t_block	*lines;
	int		i = 0;
	int		j = 0;
	int		k = 0;
	
	map_info->lines = NULL;
	int line_count = count_lines(map);
	lines = ft_malloc(sizeof(t_block) * (line_count + 1));

	while(map[i] != NULL)
	{
		j = 0;
		while(map[i][j] != '\0')
		{
			if (map[i][j] == 'L' && map[i][j + 1] == 'i' && map[i][j + 2] == 'n' && map[i][j + 3] == 'e' && map[i][j + 4] == ' ')
			{
				lines[k] = get_line(get_next_string(map[i], "Line = "));
				k++;
			}
			j++;
		}
		i++;
	}
	lines[k].x = -1;
	lines[k].y = -1;
	return (lines);
}

t_block *init_generators(t_map *map_info, char **map)
{
	t_block	*generators;
	int		i = 0;
	int		j = 0;
	int		k = 0;
	
	map_info->generators = NULL;
	int generator_count = count_c(map, 'G');
	generators = ft_malloc(sizeof(t_block) * (generator_count + 1));

	while(map[i] != NULL)
	{
		j = 0;
		while(map[i][j] != '\0')
		{
			if (map[i][j] == 'G')
			{
				generators[k].x = j + 0.5;
				generators[k].y = i	+ 0.5;
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

t_block    *init_map_block(t_map *map_info)
{
    t_block    *blocks;
    int        k;
    
    map_info->blocks = NULL;
    blocks = ft_malloc(sizeof(t_block));
    k = 0;
    blocks[k].x = -1;
    blocks[k].y = -1;
    blocks[k].id = -1;
    blocks[k].s_x = -1;
    blocks[k].s_y = -1;
    blocks[k].type = '\0';
    return (blocks);
}

t_sprite *get_portals(char **map)
{
	int k = 0;
	t_texture **sprite_texture = ft_malloc(sizeof(t_texture) * 5);
	int count = count_c(map, 'P');
	t_sprite *sprite = ft_malloc(sizeof(t_sprite) * (count + 1));
	int i = 0;
	
	while (i < 5)
	{
		sprite_texture[i] = ft_malloc(sizeof(t_texture));
		char *path_file = ft_strjoin("assets/portal_closed/", ft_itoa(i));
		char *temp = ft_strjoin(path_file, ".xpm");
		
		sprite_texture[i]->image = get_texture_file(temp, &sprite_texture[i]->width, &sprite_texture[i]->height);
		sprite_texture[i]->data = mlx_get_data_addr(sprite_texture[i]->image, &sprite_texture[i]->bpp, &sprite_texture[i]->size_line, &sprite_texture[i]->endian);
		ft_free(temp);
		ft_free(path_file);
		i++;
	}
	i = 0;
	int j = 0;
	while(map[i] != NULL)
	{
		j = 0;
		while(map[i][j] != '\0')
		{
			if (map[i][j] == 'P')
			{
				sprite[k].x = j;
				sprite[k].y = i;
				sprite[k].frames = 5;
				sprite[k].sprite_tex = sprite_texture;
				sprite[k].width = sprite_texture[0]->width;
				sprite[k].height = sprite_texture[0]->height;		
				sprite[k].type = 'P';
				k = k + 1;
			}
			j++;
		}
		i++;
	}
	sprite[k].x = -1;
	sprite[k].y = -1;
	sprite[k].frames = -1;
	sprite[k].sprite_tex = NULL;
	sprite[k].width = -1;
	sprite[k].height = -1;
	sprite[k].type = '\0';
	return (sprite);
}

t_point *get_portals_points(char **map)
{
	int k = 0;
	int count = count_c(map, 'P');
	t_point *portals = ft_malloc(sizeof(t_point) * (count + 1));
	int i = 0;
	int j = 0;
	
	while(map[i] != NULL)
	{
		j = 0;
		while(map[i][j] != '\0')
		{
			if (map[i][j] == 'P')
			{
				printf("x: %d, y: %d\n", j, i);
				portals[k].x = j;
				portals[k].y = i;
				k = k + 1;
			}
			j++;
		}
		i++;
	}

	portals[k].x = -1;
	portals[k].y = -1;
	return (portals);
}

void open_portal(int i)
{
    int x = 0;
    int y = 0;

    x = cube()->map->portals[i].x;
    y = cube()->map->portals[i].y;
    
    remove_sprite(x, y);
    add_sprite("assets/portal_opened/", 17, x, y);
}


t_sprite *init_map_sprites(t_map *map_info, char **map)
{
	t_sprite	*sprites;
	int			i;
	int			j;
	int			k;
	
	map_info->facing = NULL;
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
	map_info->sprites = NULL;
	get_2d_map(map_info, map, size);
	get_map_sizes(map_info, map_info->map);
	check_valid(map_info->map, map_info);
	map_info->doors = init_block(map_info, 'D');
	map_info->lines = init_line(map_info, map);
	map_info->blocks = init_map_block(map_info);
	map_info->generators = init_generators(map_info, map);
	map_info->sprites = get_portals(map);
	map_info->portals = get_portals_points(map);
	map_info->facing = init_map_sprites(map_info, map);
	map_info->sprite_count = count_c(map, 'P') * 64;
	
	map_info->editor_mode = false;
	return (map_info);
}
