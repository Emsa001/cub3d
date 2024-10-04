/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:21:11 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 20:28:01 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./ft_async/includes/ft_async.h"
# include "fcntl.h"
# include "ft_destructor/ft_alloc.h"
# include "items.h"
# include "keyhooks.h"
# include "libft.h"
# include "map.h"
# include "minimap.h"
# include "mlx/mlx.h"
# include "player.h"
# include "textures.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>
# include "economy.h"

# define NONE -1
# define STORE 1
# define GENERATOR 2
# define INVENTORY 3
# define MATH 4
# define PAUSE 255

# define YELLOW "\033[1;33m"
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

// math constants
# define PI 3.14159265359
# define P2 PI / 2 // TODO: norm error
# define P3 3 * PI / 2 // TODO: norm error
# define DR 0.0174533

# define T_SIZE 64
# define BLOCK_SIZE 64
# define WIDTH 1920
# define HEIGHT 1080
# define CENTER_WIDTH WIDTH / 2 // TODO: norm error
# define CENTER_HEIGHT HEIGHT / 2 // TODO: norm error
# define WIDTH_SCALE 5

# define CHAR_WIDTH 32
# define CHAR_HEIGHT 32
# define CHARS_PER_ROW 16

# define WALL '1'
# define DOOR 'D'
# define MAX_TORCHES 100
# define SPRITE_THICKNESS 5

# define M_PI 3.14159265358979323846
# define NUM_THREADS 10

typedef struct s_render	t_render;

typedef struct s_line
{
	int			start_y;
	float		tex_y;
	int			end_y;
	int			color;
	float		step;
}						t_line;

typedef struct s_cube
{
	char				*some_value;
	int					keycode;

	double				delta_time;
	t_button_node		*buttons;
	t_item				items[328];

	t_map				*map;

	int					add_money;
	pthread_mutex_t		add_money_mutex;
	bool				is_special;

	bool				paused;
	int					async_id;

	pthread_mutex_t		pause_mutex;

	t_render			*render;
	t_player			*player;
	t_textures			*textures;

	int					levels;
	int					next_portal;
}						t_cube;

typedef struct s_string
{
	char				*str;
	int					x;
	int					y;
	int					color;
	float				size;
	int					time;
	int					background;
	int					padding;

	void				*clean;
	struct s_string		*next;
}						t_string;

typedef struct s_image
{
	void				*img;
	int					x;
	int					y;
	float				size;

	int					time;
	struct s_image		*next;
}						t_image;

typedef struct s_functions
{
	void				(*func)(void *);
	struct s_functions	*next;
}						t_functions;

typedef struct s_render
{
	void				*mlx;
	void				*win;
	void				*img_ptr;
	char				*data;

	int					bpp;
	int					size_line;
	int					endian;
	int					side;
	float				ray_angle;

	int					mouse_x;
	int					mouse_y;

	double last_time;
	int frame_count;
	double fps;
	double fps_update_time;

	int quaility;

	t_image				*image_queue;
	t_string			*string_queue;
	t_functions			*functions_queue;

	pthread_mutex_t		string_queue_mutex;
	pthread_mutex_t		image_queue_mutex;
	pthread_mutex_t		functions_queue_mutex;
	pthread_mutex_t 	quality_mutex;
}						t_render;

typedef struct s_float
{
	float				x;
	float				y;
}						t_float;

typedef struct s_string_params
{
    int char_index;
    int x;
    int y;
    int color;
    float size;
} t_string_params;

typedef struct s_sprite_coords
{
	float				x;
	float				y;
	float				dist;
	int					height;
	int 				tex_x;
	t_texture			**sprite_tex;
	int frames;
}						t_sprite_coords;

typedef struct s_gen_coords
{
	float				dist;
	bool 				save;
	float				x;
	float				y;
	int					tex_x;
	int					height;
	int					height_top;
	float				tall;
	float 				top;
	bool			first_touch;
}						t_gen_coords;

typedef struct s_draw
{
	// only walls
	float				x;
	float				y;
	int					dist;
	int					tex_x;
	float 				tex_y;
	float				angle;
	float				height;
	int					start_x;
	int					start_y;
	float 				cosangle;
	float 				sinangle;
	t_texture			*texture;
	int					colors[HEIGHT + 1];
	// only generators
	t_gen_coords		gen;
	// only sprites
	bool 				is_sprite;
	bool				is_facing;
	t_sprite_coords		*sprites;
	t_sprite_coords		*facing;
	int 				s_count;
	int 				f_count;

	int					*sprite_order;

}						t_draw;

typedef struct s_thread_params
{
	int					start;
	int					end;
	float				angle_offset;
	float				fov_in_radians;

	int					color;

	t_cube				*cube;
	t_render			*render;
	t_player			*player;
	t_textures			*textures;
	pthread_t			thread_id;
}						t_thread_params;


typedef struct s_vars
{
	float				x;
	float				y;
	float				x1;
	float				y1;
	float				x2;
	float				y2;
	float				dx;
	float				dy;
	float				d;
	float				u;
}						t_vars;

/* ENGINE */
t_render				*init_render(t_render *r);
t_render				*render(void);
void					update_fps(void);
void					init_items(void);
void					render_image_async(t_image *img);

void					check_params(char **av);
t_cube					*cube_init(t_cube *c);
t_cube					*cube(void);
void					start_game(void);
void					init_hooks(void);

int						render_scene_multithread(void);
int						render_scene_singlethread(t_cube *c);

int						render_scene(t_cube *p);
bool					is_touching(float px, float py, const t_cube *c);
bool					touch_block(t_block *blocks, float px, float py);
int						touch_sprite(t_sprite *sprites, float px, float py);
int						touch_line(t_block *lines, float px, float py);
bool					touch_generator(t_block *lines, float px, float py);
void					button_click(int type, int x, int y);
void					button_tooltip(int x, int y);

void					create_image(t_render *r, int width, int height);
void					add_button(t_button *button);
void					start_case(void *arg);

/* DRAW */
t_texture				*get_wall_side(int side, const t_textures *texs, int n);
int						get_texture_color(t_texture *tex, float dist, t_draw *draw);
t_texture				*get_texture(int start_y, int height, t_thread_params *params);
void					draw_scene(t_draw *draw, t_thread_params *params);
int						darken_color_wall(int color, float factor, float wall_x,
							float wall_y);

void	get_facing_coordinates(t_draw *draw, int i, int *iter);
void	get_sprite_coordinates(t_draw *draw, int i, int *iter);
bool	touch_facing(t_draw *draw, t_float p, t_float s, int width);

t_draw	init_draw(void);
void	direction(t_draw *draw, t_thread_params *params);
void	put_line(t_draw draw, t_thread_params *params);
bool	find_hitbox(t_draw *draw, t_cube *c, int *iter);
float	get_check(int *start_y, int *end_y, float *step, float height);

void					draw_line(t_draw draw, t_thread_params *params);
void	draw_sprite(t_draw *draw, t_thread_params *params);
// generator
void draw_generators(t_draw *draw, t_thread_params *params);


long					current_frame(int frames);

// String
void					render_string(t_string *str);
int						vert_offset(const t_player *p);
int						darken_color(int color, float dist);
float					view_current_distance(const t_player *p, int start_y,
							float angle);
t_draw					init_draw(void);

// updating
void					minimap_init(void);
void					destroy_buttons(void);
void					render_string_async(t_string *str);
/* MLX */

double					deg_to_rad(double angle);

void					*load_image(char *path);
void					draw_image(void *img, int x, int y);
void					destroy_image(void *img);
void					clean_window(void);
void					put_pixel(int x, int y, int color, t_render *r);
void					put_image(t_texture *img, int x, int y, float size);

/* EXIT */
void					exit_game(int code);
void					ft_error(char *str);

/* BLOCK */
int						get_block_id(t_block *blocks, float px, float py,
							float angle);
int						block_count(t_map *map_info, char c);
void					catch_block(float angle);
void					add_block(float angle);
void					remove_block(float angle);
void 					put_string(char *str, int x, int y, int color);
void					move_door(t_map *map, t_player *p, bool opening);
int						get_side(int x, int y, char **map);

/* KeyBoard */

int						key_down(int keycode);
int						key_up(int keycode);

/* Mouse */
int						mouse_click(int button);
int						mouse_move(int x, int y);

void					hide_mouse(void);

void					item_button(t_button *button, float size);

void					put_image_queue(t_render *r);

void					put_string_queue(t_render *r);

void					button_hover(int x, int y);

void					init_economy(void);
int						random_int(int min, int max);

void					render_view(t_cube *c);
void					clear_image_queue(t_render *r);
void					clear_string_queue(t_render *r);
void					execute_button_hover(void);
void					string_timer(int time, t_location *location);
void					interaction_notify(char *str);

bool					is_paused(void);
void					set_paused(bool paused);
void					math_gui(void);
bool					check_if_point_is_on_line(t_block line, float px,
							float py);
void 					draw_background(t_string *s);

int		get_quality(t_render *r);
void	update_quality(t_render *r, int quality);
float	ft_float_atoi(char *str);

#endif
