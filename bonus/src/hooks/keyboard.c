/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:33:44 by escura            #+#    #+#             */
/*   Updated: 2024/09/07 13:43:17 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Existing key press function
int key_down(int keycode)
{
    t_cube *c = cube();

    if (keycode == ESC)
        c->paused = !c->paused;

    if(c->paused)
        return (0);

    player_keydown(keycode);
    return (0);
}

// Existing key release function
int key_up(int keycode)
{
    player_keyup(keycode);
    return (0);
}
