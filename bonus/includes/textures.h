/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:41:47 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 17:30:28 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

#define NO_MIRROR 0
#define HORIZONTAL_MIRROR 1
#define VERTICAL_MIRROR 2
#define BOTH_MIRROR 3

typedef struct s_texture
{
	void		*image;

	int			bpp;
	int			size_line;
	int			endian;
	char		*data;

	int			width;
	int			height;

}				t_texture;

typedef struct s_textures
{
	t_texture	*font;

	t_texture	*sky;
	t_texture	*floor;

	t_texture	*wall_north;
	t_texture	*wall_south;
	t_texture	*wall_east;
	t_texture	*wall_west;

	t_texture	*door;

	t_texture	*player;

	t_texture	*healthhud;
	t_texture	*healthbar;
	t_texture	*healthIcon[4];

	t_texture	*inventoryPlayer;
	t_texture	*inventoryGui;
	t_texture	*items[256];
	t_texture	*tooltip_bg;
}				t_textures;

void			*get_texture_file(char *file, int *width, int *height);
void			resize_texture(const t_texture *src, t_texture *dst,
					int new_width, int new_height);
t_texture *rotate_texture(t_texture *texture, double angle, int mirror_mode);

t_textures		*init_textures(t_textures *t);
void			init_items_textures(t_textures *t);
t_textures		*textures(void);

#endif