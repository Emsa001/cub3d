/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:47:33 by escura            #+#    #+#             */
/*   Updated: 2024/10/06 15:30:39 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# define MAX_SIZE 1000

# include "cub.h"

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
}			t_map;

void		init_map(char *av);
void		print_map(char **map);
int			ft_strlen_space(char *s);
int			ft_check_line(char *line);
t_map		*check_map(char **map, int size);
char		*ft_remove_substr(char *str, char *sub);
char		*get_next_string(char *line, char *str);
void		check_valid(char **map, t_map *map_info);
char		*ft_strstr(char *haystack, char *needle);
void		get_map_sizes(t_map *map_info, char **map);
void		get_player_position(char **map, bool first);
void		get_no_so_we_ea(t_map *map_info, char **map);
int			get_color(char **map, char *c);
void		get_2d_map(t_map *map_info, char **map, int size);
t_point		*get_begin_points(char **map, t_point *begin_points);
void		fill_loop(char to_fill[], t_point *begin_points, t_map *map_info,
				t_point size);

#endif