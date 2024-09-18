/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:24:21 by escura            #+#    #+#             */
/*   Updated: 2024/09/18 17:08:09 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void generators()
{
    const t_player *p = player();
    const t_cube *c = cube();

    bool can_open = is_nerby('G');

    if(can_open){
        t_string str;
        str.str = "Press G to open the generator";
        str.color = 0x00FF00;
        str.size = 0.7;
        str.x = CENTER_WIDTH - 250;
        str.y = HEIGHT -100;

        render_string(&str);
        // render_string("Press G to open the shop", CENTER_WIDTH - 210, HEIGHT -100, 0x00FF00, 0.7);
    }
}