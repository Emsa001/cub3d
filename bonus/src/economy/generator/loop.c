/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:24:21 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 13:27:02 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void generators()
{
    t_player *p = player();
    const t_cube *c = cube();

    t_location *find = is_nerby('G');

    if(find){
        p->GUI_temp = GENERATOR;
        p->generator = get_generator(find->x, find->y);
       
        interaction_notify("Press G to open a Generator");
    } else if(p->GUI_temp == GENERATOR){
        p->GUI_temp = NONE;
        p->GUI = NONE;
        printf("You left the generator\n");
    }

    // ft_free(find);

    if(p->GUI == GENERATOR)
        generator_gui();
}