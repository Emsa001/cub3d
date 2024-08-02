/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:33:44 by escura            #+#    #+#             */
/*   Updated: 2024/08/02 22:12:09 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

// Existing key press function
int key_down(int keycode)
{
    t_player *p = player();

    if (keycode == ESC)
        exit_game();
    
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
        p->speed = SPRINTSPEED;
    if(keycode == SPACE && p->z <= -0.5)
        p->jump_speed = JUMP_SPEED;

    if(keycode == MINUS){
        if(p->fov > 30)
            p->fov -= 5;
    }
    if(keycode == PLUS)
        if(p->fov < 120)
            p->fov += 5;
    
    if(keycode == E)
        p->interact = true;
    if(keycode == I)
        p->spawn = true;
    if(keycode == O)
        p->remove = true;
    if(keycode == F)
        p->catch = true;

    return (0);
}

// Existing key release function
int key_up(int keycode)
{
    t_player *p = player();
    
    if (keycode == W )
        p->btn_w = false;
    if (keycode == S )
        p->btn_s = false;
    if (keycode == A)
        p->btn_a = false;
    if (keycode == D)
        p->btn_d = false;
    if(keycode == SHIFT)
        p->speed = WALKSPEED;
    
    if(keycode == LEFT){
        p->btn_left = false;
    }
    if(keycode == RIGHT){
        p->btn_right = false;
    }
    
    if(keycode == UP)
        p->btn_up = false;
    if(keycode == DOWN)
        p->btn_down = false;

    if(keycode == E)
        p->interact = false;
    if(keycode == I)
        p->spawn = false;
    if(keycode == O)
        p->remove = false;
    if(keycode == F)
    {
        p->catch = false;
        p->catched = false;
    }

    return (0);
}
