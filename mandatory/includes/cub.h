/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:05:39 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/03 19:16:29 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "fcntl.h"
# include "ft_destructor/ft_alloc.h"
# include "libft.h"
# include "map.h"
# include "mlx/mlx.h"
# include "player.h"
# include "textures.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
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
# define E 101
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363
# define SHIFT 65505

# define MINUS 45
# define PLUS 61

// math constants
// # define P2 (PI / 2)
// # define P3 (3 * PI / 2)
# define PI 3.14159265359
# define P2 1.57079632679
# define P3 4.71238898038
# define DR 0.0174533

# define T_SIZE 64
# define BLOCK_SIZE 64
# define WIDTH 1920
# define HEIGHT 1080
// # define CENTER_WIDTH (WIDTH / 2)
// # define CENTER_HEIGHT (HEIGHT / 2)
# define CENTER_WIDTH 960
# define CENTER_HEIGHT 540

# define WALL '1'

typedef struct s_cube
{
	void	*mlx;
	void	*win;
	char	*some_value;
	int		keycode;

	float	tex_x;
	t_map	*map;
}			t_cube;

typedef struct s_render
{
	void	*mlx;
	void	*win;
	void	*img_ptr;
	char	*data;

	int		bpp;
	int		size_line;
	int		endian;
	int		side;

}			t_render;

/* ENGINE */
t_render	*init_render(t_render *r);
t_render	*render(void);

t_cube		*init_cube(t_cube *c);
t_cube		*cube(void);
void		start_game(void);
void		init_hooks(void);
int			render_scene(void);
void		render_view(void);
bool		is_touching(float px, float py);
float		distance(float x1, float y1, float x2, float y2);
int			get_pixel_from_image(int x, int y, int side);

/* DRAW */
void		draw_line(float angle, int i);

/* MLX */
void		*load_image(char *path);
void		draw_image(void *img, int x, int y);
void		destroy_image(void *img);
void		clean_window(void);
void		put_pixel(int x, int y, int color);

/* EXIT */
void		exit_game(int code);
void		ft_error(char *str);

#endif
