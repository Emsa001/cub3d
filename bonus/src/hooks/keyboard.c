/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:33:44 by escura            #+#    #+#             */
/*   Updated: 2024/08/23 14:48:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

// Existing key press function
int key_down(int keycode)
{
    if (keycode == ESC)
        exit_game(0);

    player_keydown(keycode);

    return (0);
}

// Existing key release function
int key_up(int keycode)
{
   
    player_keyup(keycode);

    return (0);
}
