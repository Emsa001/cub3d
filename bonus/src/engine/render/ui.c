/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:04:58 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 19:45:46 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_ui()
{
    t_player *p = player();
    p->mouse_hook = true;

    render_minimap();
    hud_inventory();
    hud_currency();
    if(p->store->open)
        open_store();

    if(cube()->paused)
        pause_game();

}