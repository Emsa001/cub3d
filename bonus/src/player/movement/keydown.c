/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:44:25 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 13:32:05 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void player_keydown(int keycode){
    t_player *p = player();
    const t_cube *c = cube();
    
    if (keycode == W)
        p->btn_w = true;
    if (keycode == S)
        p->btn_s = true;
    if (keycode == A)
        p->btn_a = true;
    if (keycode == D)
        p->btn_d = true;
    
    if(keycode == LEFT){
        p->btn_left = true;
    }
    if(keycode == RIGHT){
        p->btn_right = true;
    }
    if(keycode == UP)
        p->btn_up = true;

    if(keycode == DOWN)
        p->btn_down = true;
    
    if(keycode == SHIFT)
        p->speed = SPRINTBONUS * c->delta_time;
        
    if(keycode == SPACE && p->z <= 0.6)
        p->jump_height = JUMP_HEIGHT;

    // if(keycode == MINUS){
    //     if(p->fov > 30)
    //         p->fov -= 5;
    // }
    // if(keycode == PLUS)
    //     if(p->fov < 120)
    //         p->fov += 5;
    
    if(keycode == P)
        p->pause = !p->pause;
    
    if(keycode == E)
        p->interact = true;
    if(keycode == I)
        p->spawn = true;
    if(keycode == O)
        p->remove = true;
    if(keycode == F)
        p->catch = true;
}
