/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:04:05 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/28 21:04:43 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# define MINIMAP_PLAYER_SIZE 10
# define MINIMAP_PLAYER_COLOR 0xbababa
# define MINIMAP_COLOR 0x1a1a1c
# define SQUARE_SIZE 32
# define MINIMAP_PIXEL_WIDTH WIDTH / 6
# define MINIMAP_PIXEL_HEIGHT WIDTH / 8
# define CORNER 6
# define FRAME_WIDTH 6
# define FRAME_COLOR 0x000000

// block colors
# define BLOCK_COLOR 0x27272a
// blue
# define DOOR_COLOR 0x0000ff
// pink
# define SHOP_COLOR 0xff00ff
// yellow
# define GENERATOR_COLOR 0xffff00
// green
# define PORTAL_COLOR 0x00ff00
# include "cub3d.h"

typedef struct s_minimap
{
	int		x;
	int		y;

	int		center_x;
	int		center_y;

	int		last_x;
	int		last_y;
}			t_minimap;

t_minimap	*minimap(void);
void		draw_player(int x, int y);
void		render_minimap(void);
void		draw_minimap_square(int x, int y);
void		draw_block(int x, int y, float angle, int c);

#endif
