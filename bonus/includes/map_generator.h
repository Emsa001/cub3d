/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:54:30 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/30 13:54:43 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_GENERATOR_H
# define MAP_GENERATOR_H

# include "cub3d.h"
# define WALL_PIX 0xFFFFFF
# define DOOR_PIX 0x0000FF
# define SHOP_PIX 0xFF00FF
# define GENERATOR_PIX 0xFFFF00
# define PORTAL_PIX 0x00FF00
# define EMPTY_PIX 0x000000

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 1280
# define PIC_WIDTH 64
# define PIC_HEIGHT 64
# define CELL_SIZE (SCREEN_WIDTH / PIC_WIDTH)
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
	int				colors[6];
	t_color_picker	*button;
}					t_data;

#endif
