/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:21:11 by escura            #+#    #+#             */
/*   Updated: 2024/06/05 13:17:40 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ft_destructor/ft_alloc.h"
# include "libft.h"
# include "mlx/mlx.h"
# include <stdio.h>

typedef struct s_cube
{
	void	*mlx;
	void	*win;
    char    *some_value;
}			t_cube;

t_cube		*init_cube(t_cube *c);
t_cube		*cube(void);
void		play(void);

#endif