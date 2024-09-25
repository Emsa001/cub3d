/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:44:25 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 19:45:19 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Existing key press function
int key_down(int keycode)
{
    t_player *p = player();
    t_cube *c = cube();
    
    if (keycode == ESC){

        // exit_game(0);
        // return ;

        if(p->GUI != -1)
            p->GUI = -1;
        else if(c->map->editor_mode){
            c->map->editor_mode = false;
        }else{
            pthread_mutex_lock(&c->pause_mutex);
            c->paused = !c->paused;
            pthread_mutex_unlock(&c->pause_mutex);
        }
    }

    if(c->paused)
        return 0;
        
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
        p->sprint = true;
        
    if(keycode == SPACE)
        p->jumping = true;

    // if(keycode == MINUS){
    //     if(p->fov > 30)
    //         p->fov -= 5;
    // }
    // if(keycode == PLUS)
    //     if(p->fov < 90)
    //         p->fov += 5;
    
    if(keycode == E)
        p->open_inventory = !p->open_inventory;
    if(keycode == I)
        p->spawn = true;
    if(keycode == O)
        p->remove = true;
    if(keycode == F)
        p->interact = !p->interact;
    if(keycode == Z)
        p->catch = true;

    if(keycode == G){
        if(p->GUI_temp != -1 && p->GUI == -1)
            p->GUI = p->GUI_temp;
        else
            p->GUI = -1;
    }

    return (0);
}

