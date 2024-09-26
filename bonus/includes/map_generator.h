/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:54:30 by btvildia          #+#    #+#             */
/*   Updated: 2024/09/26 12:55:55 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_GENERATOR_H
# define MAP_GENERATOR_H

# include "cub3d.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1280
#define PIC_WIDTH 64
#define PIC_HEIGHT 64
#define CELL_SIZE (SCREEN_WIDTH / PIC_WIDTH)

typedef struct  s_data 
{
    void        *mlx_ptr;
    void        *win_ptr;
    int         drawing;
    int         **grid;
}               t_data;

#endif
