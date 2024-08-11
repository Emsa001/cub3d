/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:41:47 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 18:00:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TEXTURES_H
# define TEXTURES_H

# include "cub.h"

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
    t_texture *wall_north;
    t_texture *wall_south;
    t_texture *wall_east;
    t_texture *wall_west;
} t_textures;

t_textures *init_textures(t_textures *t, void *mlx);
t_textures *textures(void);


#endif