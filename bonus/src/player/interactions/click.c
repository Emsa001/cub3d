/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:04:34 by escura            #+#    #+#             */
/*   Updated: 2024/08/03 17:05:01 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void player_mouseclick(int button)
{
    t_player *p = player();
    
    if (button == LEFT_CLICK)
        p->catch = true;
    if(button == RIGHT_CLICK)
    {
        p->catch = false;
        p->catched = false;
    }
}