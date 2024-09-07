/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:04:58 by escura            #+#    #+#             */
/*   Updated: 2024/09/07 14:52:18 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_ui()
{
    render_minimap();
    hud_healthbar();
    hud_inventory();

    if(cube()->paused)
        pause_game();

    if(player()->hover != NULL){
        t_button *button = player()->hover;
        if(button->hover != NULL)
            ((void (*)(void*))button->hover)(NULL);
    }    
}