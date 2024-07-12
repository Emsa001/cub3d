/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:40:10 by escura            #+#    #+#             */
/*   Updated: 2024/06/20 15:33:21 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

# define WALKSPEED 2
# define SPRINTSPEED 5
# define FOV 60

typedef struct s_player
{
    float	x;
    float	y;

    float   x_px;
    float   y_px;

    float   x_dir;
    float   y_dir;
    
    float	angle;
    double  direction;

    bool     btn_w;
    bool     btn_s;
    bool     btn_a;
    bool     btn_d;
    
    bool     btn_left;
    bool     btn_right;

    int     fov;
    int     speed;

    float plane_x;
    float plane_y;
}			t_player;

t_player *init_player(t_player *p);
t_player *player(void);
void	move_player(void);
bool touch(char c);
void render_player(void);


double view_lane_distance(float x1, float y1, float angle);


#endif