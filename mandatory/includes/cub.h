/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:21:11 by escura            #+#    #+#             */
/*   Updated: 2024/07/25 22:39:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "fcntl.h"
# include "ft_destructor/ft_alloc.h"
# include "libft.h"
# include "map.h"
# include "mlx/mlx.h"
# include "player.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include "textures.h"

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
# define E 101
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363
# define SHIFT 65505

# define MINUS 45
# define PLUS 61

// math constants
# define PI 3.14159265359
# define P2 PI / 2
# define P3 3 * PI / 2
# define DR 0.0174533

# define T_SIZE 64
# define BLOCK_SIZE 64
# define WIDTH 1280
# define HEIGHT 720
# define CENTER_WIDTH WIDTH / 2
# define CENTER_HEIGHT HEIGHT / 2

# define WALL '1'

typedef struct s_cube
{
	void	*mlx;
	void	*win;
	char	*some_value;
	int		keycode;

	float tex_x;
	t_map	*map;
}			t_cube;

typedef struct s_render
{
	void *mlx;
	void *win;
	void *img_ptr;
	char *data;

	int bits_per_pixel;
	int size_line;
	int endian;
	int side;
	
} t_render;

/* ENGINE */
t_render *init_render(t_render *r);
t_render *render(void);

void		check_params(char **av);
t_cube		*init_cube(t_cube *c);
t_cube		*cube(void);
void		start_game(void);
void		init_hooks(void);
int			render_scene(t_cube *p);
bool is_touching(float px, float py);
float 		distance(float x1, float y1, float x2, float y2);

/* DRAW */
void draw_line(float angle, int i);

/* MLX */
void		*load_image(char *path);
void		draw_image(void *img, int x, int y);
void		destroy_image(void *img);
void		clean_window(void);
void 		put_pixel(int x, int y, int color);

/* EXIT */
void		exit_game(int code);
void		ft_error(char *str);

#endif
