/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:21:11 by escura            #+#    #+#             */
/*   Updated: 2024/06/13 21:05:23 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ft_destructor/ft_alloc.h"
# include "libft.h"
# include "mlx/mlx.h"
# include "fcntl.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

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
	float 	player_x;
	float 	player_y;
	float 	player_a;
}			t_map;

typedef struct s_cube
{
	void	*mlx;
	void	*win;
    char    *some_value;
	int 	keycode;
	t_map	*map;
}			t_cube;

t_cube		*init_cube(t_cube *c);
void get_params(char *av);
t_cube		*cube(void);
void		play(void);

// get - check map
void	ft_error(char *str);
t_map	*check_map(char **map);
t_map	*get_map(char *av);
void ft_free_arr(char **array);
void print_map_info(t_map *map);


#endif
