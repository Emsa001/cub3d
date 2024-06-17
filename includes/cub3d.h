/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:21:11 by escura            #+#    #+#             */
/*   Updated: 2024/06/17 18:55:06 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "fcntl.h"
# include "ft_destructor/ft_alloc.h"
# include "libft.h"
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define YELLOW "\033[1;33m"
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

// keycodes
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363
// math constants
# define PI 3.14159265359
# define P2 PI / 2
# define P3 3 * PI / 2
# define DR 0.0174533

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
	float	player_x;
	float	player_y;
	float	player_a;
}			t_map;

typedef struct s_cube
{
	void	*mlx;
	void	*win;
	char	*some_value;
	int		keycode;
	t_map	*map;
}			t_cube;

t_cube		*init_cube(t_cube *c);
void		get_params(char *av);
t_cube		*cube(void);
void		play(void);

// get - check map
t_map		*get_map(char *av);
void		ft_error(char *str);
void		print_map(char **map);
int			ft_strlen_space(char *s);
int			ft_check_line(char *line);
void		ft_free_arr(char **array);
void		print_map_info(t_map *map);
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
