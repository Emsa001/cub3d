/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:24:21 by escura            #+#    #+#             */
/*   Updated: 2024/09/18 19:52:27 by escura           ###   ########.fr       */
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
        t_string str;
        str.str = "Press G to open the generator";
        str.color = 0x00FF00;
        str.size = 0.7;
        str.x = CENTER_WIDTH - 330;
        str.y = HEIGHT -100;

        t_texture *t = textures()->ui->button_long;
        for(int i = 0; i < 5; i++)
            put_image(t, CENTER_WIDTH - 400 + (i * t->width*0.7 - ((i-1) * 4)), HEIGHT -115, 0.7);
        render_string(&str);
    } else if(p->GUI_temp == GENERATOR){
        p->GUI_temp = NONE;
        p->GUI = NONE;
        printf("You left the generator\n");
    }

    // ft_free(find);

    if(p->GUI == GENERATOR)
        generator_gui();
}