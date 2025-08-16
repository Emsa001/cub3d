/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:54:30 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/05 18:52:47 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_GENERATOR_H
# define MAP_GENERATOR_H

# include "cub3d.h"
// orange
# define WALL_PIX 0xFFFFFF
# define DOOR_PIX 0x0000FF
# define SHOP_PIX 0xFF00FF
# define EMPTY_PIX 0x000000
# define PORTAL_PIX 0x00FF00
# define PLAYER_PIX 0xFFA500
# define GENERATOR_PIX 0xFFFF00
# define MAX_COLOR 7

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 1280
# define PIC_WIDTH 64
# define PIC_HEIGHT 64
# define BUTTON_SIZE 64

typedef struct s_color_picker
{
	int				color;
	int				start_x;
	int				start_y;
	int				end_x;
	int				end_y;
}					t_color_picker;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				drawing;
	int				**grid;
	int				colors[7];
	int				curr_color;
	t_color_picker	*button;
}					t_data;

void				free_data(t_data *data);
void				init_data(t_data *data);
void				clear_image(t_data *data);
void				save_draw_txt(t_data *data);
bool				check_num(t_data *data, int color);
void				check_curr_color(int y, t_data *data);
void				draw_button(t_data *data, t_color_picker button);
void				draw_cell(t_data *data, int x, int y, int color);

#endif
