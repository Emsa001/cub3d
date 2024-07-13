/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:41:47 by escura            #+#    #+#             */
/*   Updated: 2024/07/13 18:13:20 by btvildia         ###   ########.fr       */
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
} t_textures;

t_textures *init_textures(t_textures *t, void *mlx);
t_textures *textures(void);
int get_pixel_from_image(int x, int y, int side);


#endif