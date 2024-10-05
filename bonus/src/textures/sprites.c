/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:39:55 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/05 18:35:57 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_map *map, t_sprite sprite, bool facing)
{
	t_sprite	*new_sprites;
	int			i;
	t_sprite	*sprites;

	i = 0;
	if (facing)
		sprites = map->facing;
	else
		sprites = map->sprites;
	while (sprites[i].x != -1)
		i++;
	new_sprites = ft_malloc(sizeof(t_sprite) * (i + 2));
	copy_sprites(sprites, new_sprites);
	new_sprites[i] = sprite;
	map->sprite_count++;
	i++;
	terminate_sprite(&new_sprites, &i);
	update_sprite_pointers(map, new_sprites, facing);
}

void	remove_sprite(int x, int y)
{
	t_sprite	*sprites;
	t_sprite	*new_sprites;
	int			i;
	int			j;

	sprites = cube()->map->sprites;
	i = 0;
	j = 0;
	if (!find_sprite(x, y, &i))
		return ;
	new_sprites = ft_malloc(sizeof(t_sprite) * i);
	remove_sprite_con(new_sprites, &j, x, y);
	terminate_sprite(&new_sprites, &j);
	cube()->map->sprites = new_sprites;
	ft_free(sprites);
	cube()->map->sprite_count--;
}

t_texture	**load_sprite_textures(char *path_file, int frames)
{
	t_texture	**sprite_texture;
	int			i;
	char		*path;
	char		*temp;

	sprite_texture = ft_malloc(sizeof(t_texture) * frames);
	i = 0;
	while (i < frames)
	{
		path = ft_strjoin_itoa(path_file, i);
		temp = ft_strjoin(path, ".xpm");
		sprite_texture[i] = load_texture(temp);
		ft_free(temp);
		ft_free(path);
		i++;
	}
	return (sprite_texture);
}

void	add_sprite(char *path_file, int frames, float x, float y)
{
	t_texture	**sprite_texture;
	t_sprite	sprite;

	sprite_texture = load_sprite_textures(path_file, frames);
	sprite.x = x;
	sprite.y = y;
	sprite.frames = frames;
	sprite.sprite_tex = sprite_texture;
	sprite.width = sprite_texture[0]->width;
	sprite.height = sprite_texture[0]->height;
	sprite.type = 'S';
	init_sprite(cube()->map, sprite, false);
}

void	add_facing_sprite(char *path_file, int frames, float x, float y)
{
	t_texture	**sprite_texture;
	t_sprite	sprite;

	sprite_texture = load_sprite_textures(path_file, frames);
	sprite.x = x;
	sprite.y = y;
	sprite.frames = frames;
	sprite.sprite_tex = sprite_texture;
	sprite.width = sprite_texture[0]->width;
	sprite.height = sprite_texture[0]->height;
	sprite.type = 'S';
	init_sprite(cube()->map, sprite, true);
}
