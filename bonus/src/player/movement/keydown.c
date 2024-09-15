/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:44:25 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 19:38:28 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void player_keydown(int keycode){
    t_player *p = player();
    t_cube *c = cube();
    
    if (keycode == ESC){

        // exit_game(0);
        // return ;

        if(c->map->editor_mode){
            c->map->editor_mode = false;
        }

        pthread_mutex_lock(&c->pause_mutex);
        c->paused = !c->paused;
        pthread_mutex_unlock(&c->pause_mutex);
    }

    if(c->paused)
        return;

    if(keycode == Q){
        pthread_mutex_lock(&c->add_money_mutex);
        c->add_money += 100;
        pthread_mutex_unlock(&c->add_money_mutex);
    }

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
    //     if(p->fov < 120)
    //         p->fov += 5;
    
    if(keycode == E){
        p->open_inventory = !p->open_inventory;
        p->interact = true;
    }
    if(keycode == I)
        p->spawn = true;
    if(keycode == O)
        p->remove = true;
    if(keycode == F)
        p->catch = true;

    if(keycode == G){
        p->store->open = !p->store->open;
        p->interact = !p->interact;
    }
}
