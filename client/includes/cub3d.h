/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:06:42 by escura            #+#    #+#             */
/*   Updated: 2024/05/12 20:30:18 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "libft/libft.h"
#include "ft_destructor/ft_alloc.h"

typedef struct s_game
{
    int     width;
    int     height;
    char    *map;
}               t_game;

int	start_game(void);

#endif