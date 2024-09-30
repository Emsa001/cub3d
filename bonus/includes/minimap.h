/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:04:05 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/29 18:07:57 by btvildia         ###   ########.fr       */
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

typedef struct s_player	t_player;

typedef struct s_minimap
{
	int					x;
	int					y;

	int					center_x;
	int					center_y;

	int					last_x;
	int					last_y;
}						t_minimap;

typedef struct s_square
{
	int					x;
	int					y;
	int					color;
	float				cosangle;
	float				sinangle;
	char				c;
}						t_square;

t_minimap				*minimap(void);
void					minimap_init(void);
void					init_square(t_square *square, float angle);

void					draw_player(int x, int y);
void					render_minimap(void);
void					draw_minimap_square(int x, int y);

int						check(int x, int y);
void					check_get(t_square *square, t_point *shape, int *start);
void					rotate_coords(t_point p, t_player *player,
							t_square *square, t_minimap *m);
void					draw_blocks(t_minimap *m, t_map *map, t_player *p);

#endif