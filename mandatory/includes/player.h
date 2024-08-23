/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:40:10 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 18:00:55 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub.h"

# define WALKSPEED 2
# define SPRINTSPEED 5
# define MOUSE_SENSITIVITY 0.002
# define JUMP_SPEED 0.11
# define FOV 60

typedef struct s_events
{
    bool    btn_w;
    bool    btn_s;
    bool    btn_a;
    bool    btn_d;
    
    bool    btn_up;
    bool    btn_down;
    bool    btn_left;
    bool    btn_right;
    
}			t_events;

typedef struct s_player
{
    float	x;
    float	y;
    float   z;

    float   x_px;
    float   y_px;

    float   x_dir;
    float   y_dir;
    float   z_dir;
    
    float	angle;
    double  direction;

    bool     btn_w;
    bool     btn_s;
    bool     btn_a;
    bool     btn_d;
    
    bool     btn_up;
    bool     btn_down;
    bool     btn_left;
    bool     btn_right;
    
    int     fov;
    int     speed;
}			t_player;

t_player *init_player(t_player *p);
t_player *player(void);
void	move_player(void);
void jump_player(void);
bool touch();
void render_player(void);


double view_lane_distance(float x1, float y1, float angle);


#endif