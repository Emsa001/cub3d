/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:21:11 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 22:58:42 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "fcntl.h"
# include "ft_destructor/ft_alloc.h"
# include "items.h"
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
# include "economy.h"

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
# define WIDTH 1920
# define HEIGHT 1080
# define CENTER_WIDTH WIDTH / 2
# define CENTER_HEIGHT HEIGHT / 2

# define WALL '1'
# define DOOR 'D'
# define BLOCK '2'

# define M_PI 3.14159265358979323846
# define NUM_THREADS 10

typedef struct s_cube
{
	char					*some_value;
	int						keycode;

	double					delta_time;
	t_button_node			*buttons;
	t_item					items[256];

	t_map					*map;

	int						add_money;
	pthread_mutex_t		add_money_mutex;
	bool 					is_special;

	bool					paused;
	int						async_id;

	pthread_mutex_t			pause_mutex;
}							t_cube;

typedef struct s_image_queue
{
	void					*img;
	int						x;
	int						y;
	float					size;
	struct s_image_queue	*next;
}							t_image_queue;

typedef struct s_string
{
	char					*str;
	int						x;
	int						y;
	int						color;
	float					size;
	int						time;

	void 					*clean;
	struct s_string			*next;
}							t_string;

typedef struct s_image
{
	void					*img;
	int						x;
	int						y;
	float					size;

	int time;
	struct s_image			*next;
}							t_image;

typedef struct s_render
{
	void					*mlx;
	void					*win;
	void					*img_ptr;
	char					*data;

	int						bpp;
	int						size_line;
	int						endian;
	int						side;
	float					ray_angle;

	int						mouse_x;
	int						mouse_y;

	t_image_queue			*image_queue;
	t_string			*string_queue;
	pthread_mutex_t			string_queue_mutex;
	pthread_mutex_t			image_queue_mutex;
}							t_render;

typedef struct s_draw
{
	float					angle;
	float					x;
	float					y;
	float					first_x;
	float					first_y;
	float					last_x;
	float					last_y;
	float					sprite_x;
	float					sprite_y;
	int						sprite_height;
	int						height;
	int						height_top;
	float					wall_height;
	int						start_x;
	int						start_y;
	int						side;
	int						tex_x;
	int						dist;
	int						chest_dist;
	int						sprite_dist;
}							t_draw;

typedef struct
{
	int						start;
	int						end;
	float					angleOffset;
	float					fovInRadians;

	int						color;

	t_cube					*cube;
	t_render				*render;
	t_player				*player;
	t_textures				*textures;

	pthread_mutex_t			*mutex;
}							ThreadParams;

typedef struct s_state
{
	bool					save;
	bool					block;
	bool					door;
}							t_state;

typedef struct s_async
{
	void					(*start)(struct s_async *);
	void					(*process)(struct s_async *);
	void					(*end)(struct s_async *);
	void					*arg;

	int						time;
	int						time_elapsed;
	int						process_time;

	t_cube					*cube;
	t_player				*player;
	t_render				*render;

	struct s_async			*next;
}							t_async;

void						add_async(t_async *async);

/* ENGINE */
t_render					*init_render(t_render *r);
t_render					*render(void);
void						update_fps(void);
void						render_view(void);
void						init_items(void);
void render_image_async(t_image *img);

void						check_params(char **av);
t_cube						*cube_init(t_cube *c);
t_cube						*cube(void);
void						start_game(void);
void						init_hooks(void);

int							render_scene_multithread(t_cube *c);
int							render_scene_singlethread(t_cube *c);

int							render_scene(t_cube *p);
bool						is_touching(float px, float py, const t_cube *c);
bool						touch_block(t_block *blocks, float px, float py);
int							touch_sprite(t_block *sprites, float px, float py);
int							touch_line(t_block *lines, float px, float py);
bool						touch_chest(t_block *lines, float px, float py);
void						button_click(int type, int x, int y);
void						button_tooltip(int x, int y);

void						clean_image(t_render *r);
void						create_image(t_render *r, int width, int height);
void						show_image(t_render *r, int x, int y);
void						add_button(t_button *button);

/* DRAW */
void						draw_line(t_draw draw, ThreadParams *params);
void						draw_wall(t_draw draw, ThreadParams *params);
void						draw_floor(int height, int start_x,
								ThreadParams *params, float angle);
void						draw_sky(int height, int start_x,
								ThreadParams *params, float angle);
// Chest
void						draw_chest_top(t_draw draw, ThreadParams *params,
								float angle);
void						draw_chest(t_draw draw, ThreadParams *params,
								int tex_x, float angle);

// String
void						render_string(t_string *str);
t_texture					*get_wall_side(int side, t_textures *texs);
int							vert_offset(t_player *p);
int							darken_color(int color, float ratio);
float						view_current_distance(t_player *p, int start_y,
								float angle, float z);
t_draw						init_draw(void);

// updating
int							get_scene_pixel(int x, int y);
void						draw_circle(int center_x, int center_y, int radius,
								int color);
int							get_pixel_from_image(t_texture *t, int x, int y);
void						minimap_init(void);
void						destroy_buttons(void);
void render_string_async(t_string *str);
/* MLX */

void						*load_image(char *path);
void						draw_image(void *img, int x, int y);
void						destroy_image(void *img);
void						clean_window(void);
void						put_pixel(int x, int y, int color, t_render *r);
void						put_image(t_texture *img, int x, int y, float size);

/* EXIT */
void						exit_game(int code);
void						ft_error(char *str);

/* BLOCK */
int							get_block_id(t_block *blocks, float px, float py,
								float angle);
int							block_count(t_map *map_info, char c);
void						catch_block(float angle);
void						add_block(float angle);
void						remove_block(float angle);
void						open_door(float angle, int id);
void						close_door(float angle, int id);
void put_string(char *str, int x, int y, int color, float size);

/* KeyBoard */

int							key_down(int keycode);
int							key_up(int keycode);

/* Mouse */
int							mouse_click(int button);
int							mouse_move(int x, int y);

void						check_hooks(void);

void						item_button(t_button *button, float size);

void						add_image_queue(t_texture *img, int x, int y,
								float size, t_render *r);
void						remove_image_queue(t_image_queue **q);
void						put_image_queue(t_render *r);

void						remove_string_queue(t_string **q);
void						process_string_queue(void);
void						button_hover(int x, int y);

int random_int(int min, int max);
float random_float(float min, float max);

#endif
