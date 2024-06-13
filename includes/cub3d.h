/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:21:11 by escura            #+#    #+#             */
/*   Updated: 2024/06/13 16:01:19 by btvildia         ###   ########.fr       */
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

// struct for the game
typedef struct s_cube
{
	void	*mlx;
	void	*win;
    char    *some_value;
	int 	keycode;
	// map
	char	**map;
	int 	width;
	int 	height;
}			t_cube;

t_cube		*init_cube(t_cube *c);
t_cube		*cube(void);
void		play(void);
void get_params(char *av);

#endif
