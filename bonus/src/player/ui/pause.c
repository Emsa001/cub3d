/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:30:48 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 18:49:59 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void resume_game(){
    t_cube *c = cube();
    t_player *p = player();

    p->mouse_hook = true;
    pthread_mutex_lock(&c->pause_mutex);
    c->paused = false;
    pthread_mutex_unlock(&c->pause_mutex);
}

void pause_hover(void)
{
    const t_uitextures *t = textures()->ui;
    
    const int x = CENTER_WIDTH - t->play->width / 2;
    const int y = CENTER_HEIGHT - t->play->height / 2;
    const int new_x = x - (t->play_hover->width * 1.1 - t->play_hover->width) / 2;
    const int new_y = y - (t->play_hover->height * 1.1 - t->play_hover->height) / 2;

    put_image(t->play_hover, new_x, new_y, 1.1);
}

void exit_hover(void)
{
    const t_uitextures *t = textures()->ui;
    
    const int x = CENTER_WIDTH + 205;
    const int y = CENTER_HEIGHT + 110;
    const int new_x = x - (t->button_hover->width * 1.1 - t->button_hover->width) / 2;
    const int new_y = y - (t->button_hover->height * 1.1 - t->button_hover->height) / 2;

    put_image(t->button_hover, new_x, new_y, 1.1);
    change_image_color(t->home, 0xE52554);
    put_image(t->home, CENTER_WIDTH + 218, CENTER_HEIGHT + 118, 1.1);
    // tooltip("Exit", 0.5);
}

static void exit_button()
{
    const t_uitextures *t = textures()->ui;
    const int x = CENTER_WIDTH + 205;
    const int y = CENTER_HEIGHT + 110;

    put_image(t->button, x, y, 1);
    change_image_color(t->home, 0xFFFFFF);
    put_image(t->home, CENTER_WIDTH + 220, CENTER_HEIGHT + 120, 1);
    
    t_button button;
    button.x = x;
    button.y = y;
    button.width = t->button->width;
    button.height = t->button->height;
    button.function = &exit_game;
    button.hover = &exit_hover;
    button.arg = 1;
    add_button(&button);
}

static void put_window()
{
    const t_uitextures *t = textures()->ui;
    const int x = CENTER_WIDTH - t->window->width / 2;
    const int y = CENTER_HEIGHT - t->window->height / 2;

    put_image(t->window, x, y, 1);

    // render_string("PAUSED", CENTER_WIDTH - 140, CENTER_HEIGHT - 190, 0x00FF00, 1.5);
    // render_string("Press    to resume", CENTER_WIDTH - 280, CENTER_HEIGHT + 160, 0x00FF00, 0.5);

    t_string str;
    str.str = "PAUSED";
    str.color = 0x00FF00;
    str.size = 1.5;
    str.x = CENTER_WIDTH - 140;
    str.y = CENTER_HEIGHT - 190;
    
    render_string(&str);

    str.str = "Press    to resume";
    str.color = 0x00FF00;
    str.size = 0.5;
    str.x = CENTER_WIDTH - 280;
    str.y = CENTER_HEIGHT + 160;
    
    put_image(t->keys[1], CENTER_WIDTH - 210, CENTER_HEIGHT + 150, 2.5);
    render_string(&str);
    exit_button();
}


void pause_game()
{
    t_cube *c = cube();
    t_player *p = player();
    const t_uitextures *t = textures()->ui;

    const int x = CENTER_WIDTH - t->play->width / 2;
    const int y = CENTER_HEIGHT - t->play->height / 2;
    
    p->open_inventory = false;
    put_window();
    
    p->mouse_hook = false;
    put_image(t->play, x, y, 1);

    t_button button;
    button.x = x;
    button.y = y;
    button.width = t->play->width;
    button.height = t->play->height;
    button.function = &resume_game;
    button.hover = &pause_hover; 
    button.arg = NULL;
    add_button(&button);
}