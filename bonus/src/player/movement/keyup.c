/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:44:33 by escura            #+#    #+#             */
/*   Updated: 2024/09/13 14:50:47 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void player_keyup(int keycode){
    t_player *p = player();
    const t_cube *c = cube();

    if (keycode == W )
        p->btn_w = false;
    if (keycode == S )
        p->btn_s = false;
    if (keycode == A)
        p->btn_a = false;
    if (keycode == D)
        p->btn_d = false;
    if(keycode == SHIFT)
        p->sprint = false;
    
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
    
    if(keycode == SPACE)
        p->jumping = false;

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

}
