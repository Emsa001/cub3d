/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:41:47 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 17:33:20 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TEXTURES_H
# define TEXTURES_H

typedef struct s_texture
{
    void *image;
    
    int bpp;
    int size_line;
    int endian;
    char *data;
    
    int width;
    int height;

} t_texture;

typedef struct s_textures
{
    t_texture *sky;
    t_texture *floor;

    t_texture *wall_north;
    t_texture *wall_south;
    t_texture *wall_east;
    t_texture *wall_west;

    t_texture *door;
} t_textures;

t_textures *init_textures(t_textures *t, void *mlx);
t_textures *textures(void);
int get_pixel_from_image(int x, int y, int side);


#endif