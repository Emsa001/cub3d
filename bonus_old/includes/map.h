/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:47:33 by escura            #+#    #+#             */
/*   Updated: 2024/08/21 19:34:27 by escura           ###   ########.fr       */
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

#define L_WIDTH 6

# include "cub3d.h"

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

typedef struct s_minimap
{
	float size;
	int radius;

	int x;
	int y;
}			t_minimap;

typedef struct minimap_utils{
    float center_x;
    float center_y;
    float start_x;
    float start_y;
    float end_x;
    float end_y;
}             t_minimap_utils;


typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*f;
	int		*c;
	t_block	*doors;
	t_block	*blocks;
	t_block *lines;

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
int touch_line(t_block *lines, float px, float py);
t_map		*check_map(char **map, int size);
char		*ft_remove_substr(char *str, char *sub);
char		*get_next_string(char *line, char *str);
void		check_valid(char **map, t_map *map_info);
char		*ft_strstr(char *haystack, char *needle);
void		get_map_sizes(t_map *map_info, char **map);
void		get_no_so_we_ea(t_map *map_info, char **map);
int			*get_color(t_map *map_info, char **map, char c);
void		get_2d_map(t_map *map_info, char **map, int size);
t_point		*get_begin_points(char **map, t_point *begin_points);
void		fill_loop(char to_fill[], t_point *begin_points, t_map *map_info,
				t_point size);

t_minimap *minimap();

void render_minimap();

void minimap_draw_player();
void minimap_block(int x, int y, int screen_x, int screen_y);

float minimap_center_x(void);
float minimap_center_y(void);

#endif