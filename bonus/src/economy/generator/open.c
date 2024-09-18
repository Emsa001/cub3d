/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:24:31 by escura            #+#    #+#             */
/*   Updated: 2024/09/18 19:52:17 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void window_gui(int x, int y){
    t_texture *window = textures()->ui->window;

    put_image(window, x,y, 1);
    
    t_string str;
    str.str = "GENERATOR";
    str.color = 0x00FF00;
    str.size = 1.5;
    str.x = x + 90;
    str.y = y + 20;

    render_string(&str);    
}

static void info_gui(int x, int y){
    t_player *p = player();
    t_generator *gen = p->generator;

    char *genstr = ft_itoa(gen->generated);
    char *energystr = ft_itoa(gen->energy);
    char *addstr = ft_itoa(gen->add_money);
    
    char *generated = ft_strjoin("Generated: ", genstr);
    char *energy = ft_strjoin("Energy: ", energystr);
    char *add_temp = ft_strjoin("Generating: ", addstr);
    char *add = ft_strjoin(add_temp, " / sec");
    ft_free(add_temp);
    
    put_string(add, x + 20, y + 160, 0x00FF00, 0.5);
    put_string(generated, x + 20, y + 100, 0x00FF00, 0.5);
    put_string(energy, x + 20, y + 130, 0x00FF00, 0.5);


    ft_free(genstr);
    ft_free(energystr);
    ft_free(addstr);

    ft_free(generated);
    ft_free(energy);
    ft_free(add);
}

void buy_upgrade(){
    t_player *p = player();
    t_generator *gen = p->generator;

    if(p->money < 10)
        return ;

    p->money -= 10;
    set_addmoney(10, gen);
}

void generator_upgrade(int x, int y){
    t_player *p = player();
    t_generator *gen = p->generator;

    t_button button;
    button.x = x + 20;
    button.y = y + 300;
    button.width = 64;
    button.height = 64;
    button.function = &buy_upgrade;
    button.hover = NULL;
    add_button(&button);

    t_texture *t = textures()->ui->button;
    put_image(t, x+20, y+300, 1);

}

void generator_gui()
{
    t_player *p = player();
    
    p->mouse_hook = false;

    t_generator *gen = p->generator;

    t_texture *window = textures()->ui->window;
    int x = CENTER_WIDTH - window->width / 2;
    int y = CENTER_HEIGHT - window->height / 2;

    window_gui(x,y);
    info_gui(x,y);
    generator_upgrade(x,y);
}