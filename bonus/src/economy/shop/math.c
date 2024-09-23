/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:39:01 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 19:13:57 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void window_gui(int x, int y, t_texture *window){
    put_image(window, x,y, 1);
    
    t_string str = {0};
    str.str = "WHAT IS ... ?";
    str.color = 0x7dd3fc;
    str.size = 1;
    str.x = x + 90;
    str.y = y + 10;

    render_string(&str);    


    char *streak_str = ft_itoa(player()->streak);
    char *str2 = ft_strjoin("Streak: ", streak_str);

    t_string streak = {0};
    streak.str = str2;
    streak.color = 0xfb7185;
    streak.size = 0.5;
    streak.x = x + 220;
    streak.y = y + 50;

    render_string(&streak);  
    ft_free(streak_str);
    ft_free(str2);  
}

void *empty(void *){
    return NULL;
}

void select_math(void *arg){
    int num = (int)arg;
    t_player *p = player();

    p->math_selected = num; 
}

static void choices(int x, int y){
    int i = 0;

    t_player *p = player();
    t_button *hover = p->hover;
    t_texture *button_hover_t = textures()->ui->button_hover;

    while(i < 3){
        char *num = ft_itoa(p->random[i]);
        int num_length = ft_strlen(num);

        t_button button = {0};
        button.x = x + 12 + (i * 200);
        button.y = y + 200;
        button.size = 2;
        button.is_default = true;
        button.hover = &empty;
        button.function = &select_math;
        button.arg = p->random[i];
        add_button(&button);

        if(hover != NULL && hover->x == button.x && hover->y == button.y || p->math_selected == p->random[i])
            put_image(button_hover_t, button.x, button.y, button.size);

        float size = 2;
        if(num_length > 1)
            size = 1.4;

        float string_width = num_length * size * 32; 

        t_string string = {0};
        string.str = num;
        string.color = 0x00FF00;
        string.size = size;
        string.x = button.x + (180 / 2) - (string_width / 2);
        string.y = button.y + 56;
        render_string(&string);

        ft_free(num);
        i++;
    }

}

void math_gui()
{
    t_player *p = player();

    if(p->GUI != MATH)
        return;

    p->mouse_hook = false;

    t_texture *window = textures()->ui->window;

    int x = CENTER_WIDTH - window->width / 2;
    int y = CENTER_HEIGHT - window->height / 2;

    window_gui(x,y, window);

    char *num1 = ft_itoa(p->math[0]);
    char *num2 = ft_itoa(p->math[1]);

    char *str = ft_strjoin(num1, " + ");
    char *str2 = ft_strjoin(str, num2);
    char *str3 = ft_strjoin(str2, " = ?");

    t_string string = {0};
    string.str = str3;
    string.color = 0x00FF00;
    string.size = 0.8;
    string.x = x + 180;
    string.y = y + 100;
    render_string(&string);

    ft_free(num1);
    ft_free(num2);

    ft_free(str);
    ft_free(str2);
    ft_free(str3);

    choices(x,y);
}