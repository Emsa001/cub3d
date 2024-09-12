/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:47:33 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 17:21:08 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# define MAX_SIZE 1000

#define MINIMAP_BLOCK_SIZE 48
#define MINIMAP_COLOR 0x27272a

#define MINIMAP_PIXEL_WIDTH 400
#define MINIMAP_PIXEL_HEIGHT 400
#define MINIMAP_RADIUS 300 

#define PLAYER_SIZE 5
#define PLAYER_DOT_COLOR 0x3b82f6

#define L_WIDTH 2

# include "cub3d.h"

typedef struct s_texture t_texture;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_block
{
	float x;
	float y;

	float s_x;
	float s_y;

	int			id;
	char		type;
}				t_block;

typedef struct t_sprite
{
	float x;
	float y;
	int frames;
	int width;
	int height;
	
	char type;

	t_texture	**sprite_tex;
} t_sprite;


typedef struct s_minimap
{
	float		size;
	int			radius;

	int			x;
	int			y;
}				t_minimap;

typedef struct minimap_utils
{
	float		center_x;
	float		center_y;
	float		start_x;
	float		start_y;
	float		end_x;
	float		end_y;
}				t_minimap_utils;


typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
	bool	portal;

	t_block	*doors;
	t_block	*blocks;
	t_block *lines;
	t_block *generators;
	t_sprite *sprites;
	
	t_minimap *minimap;
}			t_map;


void		map_init(char *av);
t_map 		*get_map();
void		print_map_info(void);
void		print_map(char **map);
int			ft_strlen_space(char *s);
int			ft_check_line(char *line);
t_block		*init_block(t_map *map_info, char c);
void		print_block_info(t_block *doors);
void		get_player_position(char **map);
t_map		*check_map(char **map, int size);
char		*ft_remove_substr(char *str, char *sub);
char		*get_next_string(char *line, char *str);
void		check_valid(char **map, t_map *map_info);
char		*ft_strstr(char *haystack, char *needle);
void		get_map_sizes(t_map *map_info, char **map);
void		get_no_so_we_ea(t_map *map_info, char **map);
void		get_2d_map(t_map *map_info, char **map, int size);
t_point		*get_begin_points(char **map, t_point *begin_points);
void		fill_loop(char to_fill[], t_point *begin_points, t_map *map_info,
				t_point size);

void add_sprite(char *path_file, int frames, float x, float y);
void remove_sprite(int x, int y);
void init_sprite(t_map *map_info, t_sprite sprite);

t_minimap *minimap();

void render_minimap();

void minimap_draw_player();
void minimap_block(int x, int y, int screen_x, int screen_y);

float minimap_center_x(void);
float minimap_center_y(void);

#endif