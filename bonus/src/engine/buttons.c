/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:16:47 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 18:09:13 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
        }
        current = current->next;
    }
}

void button_tooltip(int x, int y)
{
    t_cube *c = cube();
    t_button_node *current = c->buttons;

    // while(current != NULL)
    // {
    //     printf("Tooltip: %d\n",1);
    //     // if(x >= current->button.x && x <= current->button.x + current->button.width &&
    //     //    y >= current->button.y && y <= current->button.y + current->button.height)
    //     // {
    //     //     // player()->tooltipItem = &c->items[current->button.itemId];
    //     // }
    //     current = current->next;
    // }
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

void add_button(t_button button)
{
    t_cube *c = cube();
    t_button_node *new_node = ft_malloc(sizeof(t_button_node));
    new_node->button = button;
    new_node->next = c->buttons;
    c->buttons = new_node;

}