/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shopkeeper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:07:27 by escura            #+#    #+#             */
/*   Updated: 2024/09/27 18:44:02 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void shopkeeper()
{
    t_player *p = player();

    t_location *find = is_nearby('M');

    if(find){
        p->GUI_temp = STORE;
        interaction_notify("Press G to open a shop");
    } else if(p->GUI_temp == STORE){
        p->GUI_temp = NONE;
        p->GUI = NONE;
    }

    if(p->GUI == STORE){
        open_store();
    }
}