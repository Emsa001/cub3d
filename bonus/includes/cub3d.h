/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:21:11 by escura            #+#    #+#             */
/*   Updated: 2024/08/12 11:50:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "fcntl.h"
# include "ft_destructor/ft_alloc.h"
# include "keyhooks.h"
# include "libft.h"
# include "map.h"
# include "mlx/mlx.h"
# include "player.h"
# include "textures.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define YELLOW "\033[1;33m"
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

// math constants
# define PI 3.14159265359
# define P2 PI / 2
# define P3 3 * PI / 2
# define DR 0.0174533

# define T_SIZE 64
# define BLOCK_SIZE 64
# define WIDTH 1080
# define HEIGHT 720
# define CENTER_WIDTH WIDTH / 2
# define CENTER_HEIGHT HEIGHT / 2

# define WALL '1'
# define DOOR 'D'
# define BLOCK '2'

# define M_PI 3.14159265358979323846

typedef struct s_cube
{
	char *some_value;
	int keycode;

	float tex_x;
	t_map *map;
} t_cube;

typedef struct s_render
{
	void *mlx;
	void *win;
	void *img_ptr;
	char *data;

	int bpp;
	int size_line;
	int endian;
	int side;

} t_render;

typedef struct s_ray
{
	float x;
	float y;
	int dist;
} t_ray;

typedef struct s_state
{
    bool save;
    bool block;
    bool door;
} t_state;


typedef struct {
    int start;
    int end;
    float angleOffset;
    float fovInRadians;

	int color;

    t_cube *cube;
    t_render *render;
    t_player *player;
	t_textures *textures;
	
    pthread_mutex_t *mutex;
} ThreadParams;

/* ENGINE */
t_render	*init_render(t_render *r);
t_render	*render(void);
void 		render_view();

void		check_params(char **av);
t_cube		*cube_init(t_cube *c);
t_cube		*cube(void);
void		start_game(void);
void		init_hooks(void);

int			render_scene_multithread(t_cube *c);
int			render_scene_singlethread(t_cube *c);

int render_scene(t_cube *p);
bool is_touching(float px, float py);
bool touch_edge(float x, float y);
bool touch_block(t_block *blocks, float px, float py);
int distance(float x1, float y1, float x2, float y2);

/* DRAW */
void 		draw_line(float angle, int start_x, ThreadParams *params);
void		draw_cross_in_centre(void);
void draw_cross_in_centre(void);
void draw_cube(int x, int y, int size, int col);

// updating
void update_fps(void);
int get_scene_pixel(int x, int y);
void	draw_circle(int center_x, int center_y, int radius, int color);
int get_pixel_from_image(t_texture *t, int x, int y);
void	minimap_init(void);

/* MLX */

void *load_image(char *path);
void draw_image(void *img, int x, int y);
void destroy_image(void *img);
void clean_window(void);
void put_pixel(int x, int y, int color);

/* EXIT */
void exit_game(int code);
void		ft_error(char *str);

/* BLOCK */
int			get_block_id(t_block *blocks, float px, float py, float angle);
int			block_count(t_map *map_info, char c);
void		catch_block(float angle);
void		add_block(float angle);
void		remove_block(float angle);
void		open_door(float angle, int id);
void		close_door(float angle, int id);

#endif
