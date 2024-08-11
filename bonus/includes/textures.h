/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:41:47 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 15:44:51 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

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
	t_texture	*sky;
	t_texture	*floor;

	t_texture	*wall_north;
	t_texture	*wall_south;
	t_texture	*wall_east;
	t_texture	*wall_west;

	t_texture	*door;

	t_texture	*player;
}				t_textures;

t_textures		*init_textures(t_textures *t);
t_textures		*textures(void);
void			*get_texture_file(char *file, int *width, int *height);
int				get_pixel_from_image(t_texture *t, int x, int y);
void			resize_texture(const t_texture *src, t_texture *dst,
					int new_width, int new_height);

#endif