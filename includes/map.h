/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:47:33 by escura            #+#    #+#             */
/*   Updated: 2024/06/18 15:49:16 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H


# include "cub3d.h" 

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
	int		*f;
	int		*c;
}			t_map;

void		get_params(char **av);
t_map		*get_map(char *av);
void		ft_error(char *str);
void		print_map(char **map);
int			ft_strlen_space(char *s);
int			ft_check_line(char *line);
void		print_map_info(void);
t_map		*check_map(char **map, int size);
char		*get_next_string(char *line, char *str);
char		*ft_remove_substr(char *str, char *sub);
char		*ft_strstr(char *haystack, char *needle);
void		get_map_sizes(t_map *map_info, char **map);
void		get_no_so_we_ea(t_map *map_info, char **map);
int			*get_color(t_map *map_info, char **map, char c);
void		get_player_position(t_map *map_info, char **map);
void		get_2d_map(t_map *map_info, char **map, int size);
void		check_valid(char **map, t_map *map_info);

#endif