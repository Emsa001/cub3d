/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:51 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/12 19:42:52 by escura           ###   ########.fr       */
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

t_sprite  get_portal(char **map)
{
	t_texture **sprite_texture = ft_malloc(sizeof(t_texture) * 5);
	t_sprite sprite;
	int i = 0;
	
	while (i < 5)
	{
		sprite_texture[i] = ft_malloc(sizeof(t_texture));
		char *path = ft_strjoin("assets/portal_closed/", ft_itoa(i));
		path = ft_strjoin(path, ".xpm");
		
		sprite_texture[i]->image = get_texture_file(path, &sprite_texture[i]->width, &sprite_texture[i]->height);
		sprite_texture[i]->data = mlx_get_data_addr(sprite_texture[i]->image, &sprite_texture[i]->bpp, &sprite_texture[i]->size_line, &sprite_texture[i]->endian);
		ft_free(path);
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
				sprite.x = j;
				sprite.y = i;
				break;
			}
			j++;
		}
		i++;
	}
	printf("portal x: %f y: %f\n", sprite.x, sprite.y);
	sprite.frames = 5;
	sprite.sprite_tex = sprite_texture;
	sprite.width = sprite_texture[0]->width;
	sprite.height = sprite_texture[0]->height;
	return (sprite);
}

void init_sprite(t_map *map_info, t_sprite sprite);

t_sprite *init_map_sprite(t_map *map_info, char **map)
{
	t_sprite	*sprites;
	int			k;
	
	map_info->sprites = NULL;
	sprites = ft_malloc(sizeof(t_sprite));
	
	k = 0;
	sprites[k].x = -1;
	sprites[k].y = -1;
	sprites[k].frames = -1;
	sprites[k].sprite_tex = NULL;
	sprites[k].width = -1;
	sprites[k].height = -1;

	return (sprites);
}

void init_sprite(t_map *map_info, t_sprite sprite)
{
	t_sprite *new_sprites;
	t_sprite *tmp;
	t_sprite *sprites = map_info->sprites;
	
	int i = 0;
	while (sprites[i].x != -1)
		i++;
	new_sprites = ft_malloc(sizeof(t_sprite) * (i + 2));
	i = 0;
	while (sprites[i].x != -1)
	{
		new_sprites[i] = sprites[i];
		i++;
	}
	new_sprites[i] = sprite;
	new_sprites[i + 1].x = -1;
	new_sprites[i + 1].y = -1;
	new_sprites[i + 1].frames = -1;
	new_sprites[i + 1].sprite_tex = NULL;
	new_sprites[i + 1].width = -1;
	new_sprites[i + 1].height = -1;
	tmp = map_info->sprites;
	map_info->sprites = new_sprites;
	
	ft_free(tmp);
}


// it takes the path of the sprite exaple "assets/torch/"
// the number of frames and the position x and y where sprite will be placed
void add_sprite(char *path_file, int frames, float x, float y)
{
	t_texture **sprite_texture = ft_malloc(sizeof(t_texture) * frames);
	t_sprite sprite;
	int i = 0;
	
	while (i < frames)
	{
		sprite_texture[i] = ft_malloc(sizeof(t_texture));
		char *path = ft_strjoin(path_file, ft_itoa(i));
		char *temp = ft_strjoin(path, ".xpm");
		
		sprite_texture[i]->image = get_texture_file(temp, &sprite_texture[i]->width, &sprite_texture[i]->height);
		sprite_texture[i]->data = mlx_get_data_addr(sprite_texture[i]->image, &sprite_texture[i]->bpp, &sprite_texture[i]->size_line, &sprite_texture[i]->endian);
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
	init_sprite(cube()->map, sprite);
}

void remove_sprite(int x, int y)
{
	t_sprite *sprites = cube()->map->sprites;
	t_sprite *new_sprites;
	t_sprite *tmp;
	int i = 0;
	int j = 0;
	
	while (sprites[i].x != -1)
		i++;
	new_sprites = ft_malloc(sizeof(t_sprite) * i);
	i = 0;
	while (sprites[i].x != -1)
	{
		// if sprite on the position x and y is found it will not be added to the new_sprites array
		if (sprites[i].x == x && sprites[i].y == y)
		{
			i++;
			continue;
		}
		new_sprites[j] = sprites[i];
		i++;
		j++;
	}

	new_sprites[j].x = -1;
	new_sprites[j].y = -1;
	new_sprites[j].frames = -1;
	new_sprites[j].sprite_tex = NULL;
	new_sprites[j].width = -1;
	new_sprites[j].height = -1;
	tmp = cube()->map->sprites;
	cube()->map->sprites = new_sprites;
	ft_free(tmp);		
}

t_map	*check_map(char **map, int size)
{
	t_map	*map_info;

	map_info = ft_malloc(sizeof(t_map));
	map_info->width = 0;
	map_info->height = 0;
	map_info->portal = false;
	map_info->map = NULL;
	get_2d_map(map_info, map, size);
	get_map_sizes(map_info, map_info->map);
	check_valid(map_info->map, map_info);
	map_info->doors = init_block(map_info, 'D');
	map_info->lines = init_line(map_info, map);
	map_info->blocks = init_map_block(map_info);
	map_info->generators = init_generators(map_info, map);
	map_info->sprites = init_map_sprite(map_info, map);

	t_sprite portal = get_portal(map);
	init_sprite(map_info, portal);
	return (map_info);
}
