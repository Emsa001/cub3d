/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:16:47 by escura            #+#    #+#             */
/*   Updated: 2024/09/27 20:05:34 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void remove_button(t_button *button)
{
    t_cube *c = cube();
    t_button_node *current = c->buttons;
    t_button_node *prev = NULL;

    while(current != NULL)
    {
        if(ft_memcmp(&current->button, button, sizeof(t_button)) == 0)
        {
            if(prev == NULL)
                c->buttons = current->next;
            else
                prev->next = current->next;
            ft_free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void button_click(int type, int x, int y)
{
    t_cube *c = cube();
    t_button_node *current = c->buttons;

    while(current != NULL)
    {
        if(x >= current->button.x && x <= current->button.x + current->button.width &&
           y >= current->button.y && y <= current->button.y + current->button.height)
        {
            if (current->button.function != NULL)
            {
                printf("Function pointer is valid. Calling function...\n");
                ((void (*)(void*))current->button.function)(current->button.arg);
            }

            if(current->button.remove){
                remove_button(&current->button);
            }
            return ;
        }
        current = current->next;
    }
}

void button_hover(int x, int y)
{
    t_cube *c = cube();
    t_button_node *current = c->buttons;

    while(current != NULL)
    {
        if(x >= current->button.x && x <= current->button.x + current->button.width &&
           y >= current->button.y && y <= current->button.y + current->button.height)
        {
            ft_free(player()->hover);
            player()->hover = ft_malloc(sizeof(t_button));
            ft_memcpy(player()->hover, &current->button, sizeof(t_button));

        }
        current = current->next;
    }
}

void destroy_buttons()
{
    t_cube *c = cube();
    t_button_node *current = c->buttons;
    t_button_node *next;

    if(c->buttons == NULL)
        return;

    while(current != NULL)
    {
        next = current->next;
        if (current != NULL) {
            ft_free(current);
        }
        current = next;
    }
    c->buttons = NULL;
}

void add_button(t_button *button)
{
    t_texture *button_t = textures()->ui->button;
    t_texture *button_hover_t = textures()->ui->button_hover;
    t_button *current = player()->hover;

    if(button->is_default == true){
        if(!button->size)
            button->size = 1;

        button->width = button_t->width * button->size;
        button->height = button_t->height * button->size;
    }

    t_cube *c = cube();
    t_button_node *node = c->buttons;

    while (node != NULL) {
        if (ft_memcmp(&node->button, button, sizeof(t_button)) == 0)
            return;
        node = node->next;
    }

    // If we've reached this point, the button doesn't exist in the list
    t_button_node *new_node = ft_malloc(sizeof(t_button_node));
    ft_memcpy(&new_node->button, button, sizeof(t_button));
    new_node->next = c->buttons;
    c->buttons = new_node;

    if(button->is_default == true){
        put_image(button_t, button->x, button->y, button->size);
    }
}