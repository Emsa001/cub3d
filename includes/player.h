/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:40:10 by escura            #+#    #+#             */
/*   Updated: 2024/06/18 19:54:35 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

typedef struct s_player
{
    float	x;
    float	y;

    float   x_px;
    float   y_px;

    float   x_dir;
    float   y_dir;
    
    float	a;

    bool     btn_w;
    bool     btn_s;
    bool     btn_a;
    bool     btn_d;
}			t_player;

t_player *init_player(t_player *p);
t_player *player(void);

#endif