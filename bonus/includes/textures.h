/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:41:47 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 19:17:35 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# define NO_MIRROR 0
# define HORIZONTAL_MIRROR 1
# define VERTICAL_MIRROR 2
# define BOTH_MIRROR 3

# define PROGRESS_COVER 100
# define PROGRESS_RED 0
# define PROGRESS_YELLOW 6
# define PROGRESS_BLUE 12
# define PROGRESS_GREEN 18

typedef struct s_texture
{
	void			*image;

	int				bpp;
	int				size_line;
	int				endian;
	char			*data;

	int				width;
	int				height;

}					t_texture;

typedef struct s_uitextures
{
	t_texture		*button;
	t_texture		*button_hover;
	t_texture		*button_long;

	t_texture		*play;
	t_texture		*play_hover;
	t_texture		*home;

	t_texture		*window;
	t_texture		*panel;

	t_texture		keys[32];
	t_texture		progress[24];
	t_texture		progress_cover[3];
}					t_uitextures;

typedef struct s_textures
{
	t_texture		*font;
	int				char_pixel_data[95][32 * 32];

	t_texture		**ceiling;
	t_texture		**floor;
	t_texture		**wall_north;
	t_texture		**wall_south;
	t_texture		**wall_east;
	t_texture		**wall_west;

	t_texture		*door;

	t_texture		*player;

	t_texture		*generator;
	t_texture		*generator1;
	t_texture		*generator_top;

	t_texture		*inventory_player;
	t_texture		*inventory_gui;
	t_texture		items[328];
	t_texture		*tooltip_bg;
	t_texture		*open_portal;

	t_uitextures	*ui;
}					t_textures;

typedef struct s_rotate_vars
{
	double			red_angle;
	double			cos_a;
	double			sin_a;
	int				src_cx;
	int				src_cy;
	int				dest_cx;
	int				dest_cy;
	int				x;
	int				y;
	int				tx;
	int				ty;
	int				i;
	int				src_offset;
	int				dest_offset;
}					t_rotate_vars;

void				*get_texture_file(char *file, int *width, int *height);
char				*get_texture_name(char *dir, int i);
t_texture			*load_texture(char *dir);

t_texture			*rotate_texture(t_texture *texture, double angle,
						int mirror_mode);

t_textures			*init_textures(t_textures *t);
void				init_items_textures(t_textures *t);
void				init_ui(t_textures *t);
t_textures			*textures(void);
void				change_image_color(t_texture *img, int color);
void				destroy_textures(void);
void				destroy_texture(t_texture *texture);
t_texture			*progress_bar(int progress, int color);
void				init_progress(t_textures *t);
int					get_pixel_from_image(t_texture *t, int x, int y);

#endif