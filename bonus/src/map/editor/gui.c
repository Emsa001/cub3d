#include "cub3d.h"

void map_editor_hover(){
    tooltip("Edit the map!",0.4);
}

static void put_window()
{
    const t_uitextures *t = textures()->ui;
    const int x = 50;
    const int y = 50;

    put_image(t->window, x, y, 3);

    t_string str;
    str.str = "MAP EDITOR";
    str.color = 0x00FF00;
    str.size = 1.5;
    str.x = CENTER_WIDTH - 200;
    str.y = 200;
    
    render_string(&str);

    // str.str = "Press    to resume";
    // str.color = 0x00FF00;
    // str.size = 0.5;
    // str.x = CENTER_WIDTH - 280;
    // str.y = CENTER_HEIGHT + 160;
    
    // put_image(t->keys[1], CENTER_WIDTH - 210, CENTER_HEIGHT + 150, 2.5);
    // render_string(&str);
}

int x_btn = 0;
int y_btn = 0;

void example_click(){
    
    t_player *p = player();
    t_render *r = render();

    int x = r->mouse_x;
    int y = r->mouse_y;

    printf("You clicked at %d %d\n", x, y);

    t_image testimg = { 0 };
    testimg.img = textures()->ui->button_hover;
    testimg.x = x;
    testimg.y = y;
    testimg.size = 0.3;
    testimg.time = 1000;

    // render_image_async(&testimg);

    x_btn = x;
    y_btn = y;

}

void example_tooltip(){
    tooltip("nerd", 0.5);
}

void put_example_button(){
    
    const t_uitextures *t = textures()->ui;

    int x = 100;
    int y = 400;

    t_button button;
    button.x = x;
    button.y = y;
    button.width = t->button->width * 19.4;
    button.height = t->button->height * 6.8;
    button.function = &example_click;
    button.hover = NULL; 
    button.arg = NULL;
    add_button(&button);
    for(int i = 0; i < 5; i++){
        put_image(t->button, x + t->button->width*4.8*i - 100*i, y, 5);
    }
    for(int i = 0; i < 5; i++){
        put_image(t->button, x + t->button->width*4.8*i - 100*i, y + 200, 5);
    }
}

void map_editor_enter()
{
    t_cube *c = cube();
    t_player *p = player();
    const t_uitextures *t = textures()->ui;

    int x = CENTER_WIDTH - t->play->width / 2;
    int y = CENTER_HEIGHT - t->play->height / 2;
    
    c->map->editor_mode = true;
    p->mouse_hook = false;
    
    put_window();
    put_example_button();

    for(int i = 0; i < 5; i++){
        put_pixel(CENTER_WIDTH + i, CENTER_HEIGHT + i, 0x00FF00, render());
    }
    put_image(t->button_hover, x_btn, y_btn, 0.3);
}

