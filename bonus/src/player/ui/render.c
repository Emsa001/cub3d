/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:04:58 by escura            #+#    #+#             */
/*   Updated: 2024/09/15 15:25:53 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_ui()
{
    t_player *p = player();

    render_minimap();
    hud_inventory();
    hud_currency();
    if(p->store->open)
        open_store();

    if(cube()->paused)
        pause_game();

}