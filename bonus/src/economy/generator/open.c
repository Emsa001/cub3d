/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:24:31 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 17:18:13 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define UPDATE_ADD_MONEY 1

typedef struct generator_upgrade{
    int *type;
    int *level;
    int max_level;
    int price;
    int prize;
    int extra;

    char *name;
} t_generator_upgrade;

static void window_gui(int x, int y){
    t_texture *window = textures()->ui->window;

    put_image(window, x,y, 1);
    
    t_string str = {0};
    str.str = "GENERATOR";
    str.color = 0x00FF00;
    str.size = 1.5;
    str.x = x + 90;
    str.y = y + 20;

    render_string(&str);    
}

static void info_gui(int x, int y){
    t_player *p = player();
    const t_generator *gen = p->generator;

    pthread_mutex_lock(&gen->mutex);

    char *genstr = ft_itoa(gen->generated);
    char *randomstr = ft_itoa(gen->random);
    char *addstr = ft_itoa((gen->add_money / 5) * gen->speed);
    char *speedstr = ft_itoa(gen->speed);
    
    char *generated = ft_strjoin("Generated: ", genstr);
    char *random = ft_strjoin("Random: ", randomstr);
    char *add_temp = ft_strjoin("Generating: ", addstr);
    char *speed = ft_strjoin("Speed: ", speedstr);
    char *add = ft_strjoin(add_temp, " / sec");

    pthread_mutex_unlock(&gen->mutex);
    
    ft_free(add_temp);
    
    put_string(add, x + 20, y + 160, 0x00FF00, 0.5);
    put_string(generated, x + 20, y + 100, 0x00FF00, 0.5);
    put_string(random, x + 20, y + 130, 0x00FF00, 0.5);
    put_string(speed, x + 20, y + 190, 0x00FF00, 0.5);

    ft_free(genstr);
    ft_free(randomstr);
    ft_free(addstr);
    ft_free(speedstr);

    ft_free(generated);
    ft_free(random);
    ft_free(add);
    ft_free(speed);
}

void buy_upgrade(void *arg){
    t_player *p = player();
    t_generator *gen = p->generator;
    t_generator_upgrade *upgrade = (t_generator_upgrade *)arg;

    if(p->money < upgrade->price || *upgrade->level >= upgrade->max_level){
        return ;
    }

    add_money(-upgrade->price);
    
    pthread_mutex_lock(&gen->mutex);
    if(upgrade->type)
        *upgrade->type += upgrade->prize;
    if(upgrade->level)
        *upgrade->level += 1;
    pthread_mutex_unlock(&gen->mutex);
}

void upgrade_hover(void *arg){
    t_generator_upgrade *upgrade = (t_generator_upgrade *)arg;

    if(!upgrade || !upgrade->name)
        return ;
    tooltip(upgrade->name,0.5);
}

void generator_upgrade(int x, int y, t_generator_upgrade *upgrade)
{
    t_player *p = player();

    int btn_x = x + 120;
    int btn_y = y + 300;

    if(upgrade->max_level > *upgrade->level){
        t_button button = {0};
        
        button.x = btn_x;
        button.y = btn_y;
        button.size = 0.3;
        button.function = &buy_upgrade;
        button.hover = &upgrade_hover;
        button.arg = (void *)upgrade;
        
        button.hover_change = true;
        button.is_default = true;
        
        add_button(&button);
    }

    t_texture *cover = progress_bar(1, PROGRESS_COVER);
    t_texture *progress = progress_bar(*upgrade->level, PROGRESS_RED);
    if(!cover || !progress)
        return ;
    
    put_image(cover, btn_x - 100, btn_y - 3, 2);
    put_image(progress, btn_x - 100, btn_y - 3, 2);

    char *price_str;

    if(upgrade->max_level > *upgrade->level){
        char *price = ft_itoa(upgrade->price);
        price_str = ft_strjoin("Price: ", price);
        ft_free(price);
    }else
        price_str = ft_strdup("Max level");

    t_string str = {0};
    str.str = price_str;
    str.color = 0x00FF00;
    str.size = 0.4;
    str.x = x + 25;
    str.y = btn_y - 20;
    render_string(&str);

    ft_free(price_str);
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

    t_generator_upgrade *main = ft_calloc(1,sizeof(t_generator_upgrade));
    
    main->level = &(gen->level);
    main->type = &(gen->add_money);

    main->max_level = 5;
    main->price = gen->level * 10000;
    main->prize = gen->add_money * (gen->level + 1);
    main->extra = UPDATE_ADD_MONEY;
    main->name = "Generating";
    
    generator_upgrade(x,y, main);


    t_generator_upgrade *speed = ft_calloc(1,sizeof(t_generator_upgrade));
    speed->level = &(gen->speed);
    
    speed->max_level = 5;
    speed->price = gen->speed * 10000;
    speed->prize = 1;
    speed->name = "Speed";
    
    generator_upgrade(x,y + 50, speed);

    t_generator_upgrade *random = ft_calloc(1,sizeof(t_generator_upgrade));
    random->level = &(gen->random);
    
    random->max_level = 11;
    random->price = gen->random * 50000;
    random->prize = 1;
    random->name = "Random";
    
    generator_upgrade(x + 200,y, random);
}