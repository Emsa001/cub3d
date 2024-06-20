/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:41:47 by escura            #+#    #+#             */
/*   Updated: 2024/06/20 20:51:04 by escura           ###   ########.fr       */
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
    char *img_data;
    
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
    t_texture *wall_west
} t_textures;

t_textures *init_textures(t_textures *t, void *mlx);
t_textures *textures(void);


#endif