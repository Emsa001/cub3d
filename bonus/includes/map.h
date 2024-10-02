/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:47:33 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 18:37:54 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# define MAX_SIZE 1000
# define MAX_BLOCK 3
# define L_WIDTH 2

# include "cub3d.h"

typedef struct s_minimap	t_minimap;
typedef struct s_texture	t_texture;
typedef struct s_float		t_float;

typedef struct s_point
{
	int						x;
	int						y;
}							t_point;

typedef struct s_block
{
	float					x;
	float					y;

	float					s_x;
	float					s_y;

	int						id;
	char					type;
}							t_block;

typedef struct s_sprite
{
	float					x;
	float					y;
	int						frames;
	int						width;
	int						height;

	char					type;

	t_texture				**sprite_tex;
}							t_sprite;

typedef struct s_map
{
	int						width;
	int						height;
	char					**map;
	bool					portal;

	bool					editor_mode;
	int						sprite_count;

	t_block					*doors;
	t_block					*blocks;
	t_block					*lines;
	t_block					*generators;
	t_sprite				*sprites;
	t_sprite				*facing;
	t_point					*portals;
	t_minimap				*minimap;
}							t_map;

void						map_init(char *av);
t_map						*get_map(void);
void						open_portal(int i);
void						print_map_info(void);
void						print_map(char **map);
int							ft_strlen_space(char *s);
int							ft_check_line(char *line);
t_block						*init_door(t_map *map_info);
void						print_block_info(t_block *doors);
void						get_player_position(char **map);
t_map						*check_map(char **map, int size);
char						*ft_remove_substr(char *str, char *sub);
char						*get_next_string(char *line, char *str);
void						check_valid(char **map, t_map *map_info);
char						*ft_strstr(char *haystack, char *needle);
void						get_map_sizes(t_map *map_info, char **map);
void						get_no_so_we_ea(t_map *map_info, char **map);
void						get_2d_map(t_map *map_info, char **map, int size);
t_point						*get_begin_points(char **map,
								t_point *begin_points);
t_sprite					get_sprite(char *path_file, int frames, float x,
								float y);
void						fill_loop(char to_fill[], t_point *begin_points,
								t_map *map_info, t_point size);

void						add_sprite(char *path_file, int frames, float x,
								float y);
void						add_facing_sprite(char *path_file, int frames,
								float x, float y);
void						remove_sprite(int x, int y);
void						init_sprite(t_map *map, t_sprite sprite,
								bool facing);
void						get_points(t_point **points, char **map, char c);

int							count_c(char **map, char c);
void						terminate_blocks(t_block **blocks, int i);
void						init_once(t_block *blocks, t_float point, int *k,
								char type);

// sprites
bool						find_sprite(float x, float y, int *i);
void						copy_sprites(t_sprite *src, t_sprite *dst);
void						terminate_sprite(t_sprite **sprites, int *i);
void						update_sprite_pointers(t_map *map,
								t_sprite *new_sprites, bool facing);
t_block						*init_generators(t_map *map_info, char **map);
t_sprite					*init_map_sprites(t_map *map_info, char **map);
t_sprite					*init_map_facing(char **map);

#endif