/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:39:55 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/19 19:27:15 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_sprite(t_map *map, t_sprite sprite, bool facing)
{
	t_sprite *new_sprites;
	t_sprite *tmp;
	
	int i = 0;
	t_sprite *sprites;
	if(facing)
		sprites = map->facing;
	else
		sprites = map->sprites;

	while (sprites[i].x != -1)
		i++;
	new_sprites = ft_malloc(sizeof(t_sprite) * (i + 2));
	i = 0;
	while (sprites[i].x != -1)
	{
		new_sprites[i] = sprites[i];
		i++;
	}
	map->sprite_count++;
	new_sprites[i] = sprite;
	new_sprites[i + 1].x = -1;
	new_sprites[i + 1].y = -1;
	new_sprites[i + 1].frames = -1;
	new_sprites[i + 1].sprite_tex = NULL;
	new_sprites[i + 1].width = -1;
	new_sprites[i + 1].height = -1;

	if(facing)
	{
		tmp = map->facing;
		map->facing = new_sprites;
	}
	else
	{
		tmp = map->sprites;
		map->sprites = new_sprites;
	}
	
	ft_free(tmp);
}

void remove_sprite(int x, int y)
{
	t_sprite *sprites = cube()->map->sprites;
	t_sprite *new_sprites;
	t_sprite *tmp;
	int i = 0;
	int j = 0;
	
	while (sprites[i].x != -1)
	{
		if (sprites[i].x == x && sprites[i].y == y)
			j++;
		i++;
	}
	if (!j)
		return;

	new_sprites = ft_malloc(sizeof(t_sprite) * i);
	i = 0;
	j = 0;
	while (sprites[i].x != -1)
	{
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
	new_sprites[j].type = '\0';
	cube()->map->sprite_count--;
	tmp = cube()->map->sprites;
	cube()->map->sprites = new_sprites;
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
	sprite.type = 'S';
	init_sprite(cube()->map, sprite, false);
}

void add_facing_sprite(char *path_file, int frames, float x, float y)
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
	sprite.type = 'S';
	init_sprite(cube()->map, sprite, true);
}
