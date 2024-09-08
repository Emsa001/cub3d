/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:34:36 by escura            #+#    #+#             */
/*   Updated: 2024/09/08 17:52:29 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void remove_string_queue(t_string_queue **q)
{
    t_string_queue *tmp = (*q)->next;
    ft_free((*q)->str);
    ft_free(*q);
    *q = tmp;
}

void add_string_queue(char *str, int x, int y, int color, float size) {
    t_render *r = render();
    t_string_queue *new = ft_malloc(sizeof(t_string_queue));
    new->str = ft_strdup(str);
    new->x = x;
    new->y = y;
    new->color = color;
    new->size = size;
    new->next = NULL;

    pthread_mutex_lock(&r->string_queue_mutex);  // Lock the mutex before accessing the queue

    if (r->string_queue == NULL) {
        r->string_queue = new;
    } else {
        t_string_queue *q = r->string_queue;
        while (q->next != NULL)
            q = q->next;
        q->next = new;
    }

    pthread_mutex_unlock(&r->string_queue_mutex);  // Unlock the mutex after modifying the queue
}


void write_string_queue() {
    t_render *r = render();
    pthread_mutex_lock(&r->string_queue_mutex);  // Lock the mutex before accessing the queue

    t_string_queue *q = r->string_queue;
    while (q != NULL) {
        write_string(q->str, q->x, q->y, q->color, q->size);

        t_string_queue *tmp = q->next;
        remove_string_queue(&q);
        q = tmp;
    }

    r->string_queue = NULL;

    pthread_mutex_unlock(&r->string_queue_mutex);  // Unlock the mutex after modifying the queue
}


// https://stmn.itch.io/font2bitmap
void write_string(char *str, int x, int y, int color, float size)
{
    t_texture *font = textures()->font;
    t_render *r = render();

    const int char_width = 32;
    const int char_height = 32; 
    const int chars_per_row = 16; 

    int char_pixel_data[95][32 * 32];

    for (int index = 0; index < 95; ++index)
    {
        int row = index / chars_per_row;
        int col = index % chars_per_row;
        int src_x = col * char_width;
        int src_y = row * char_height;
        
        for (int i = 0; i < char_width; ++i)
        {
            for (int j = 0; j < char_height; ++j)
            {
                int pixel_color = get_pixel_from_image(font, src_x + i, src_y + j);
                char_pixel_data[index][i + j * char_width] = pixel_color;
            }
        }
    }

    while (*str)
    {
        char ch = *str++;
        if (ch && ch < ' ' || ch > '~') continue; 

        int char_index = ch - ' ';
        int *pixels = char_pixel_data[char_index];

        for (int i = 0; i < char_width; ++i)
        {
            for (int j = 0; j < char_height; ++j)
            {
                int pixel_color = pixels[i + j * char_width];
                if (pixel_color > 0) 
                {
                    for (int dx = 0; dx < size; ++dx)
                    {
                        for (int dy = 0; dy < size; ++dy)
                        {
                            put_pixel(x + i * size + dx, y + j * size + dy, color, r);
                        }
                    }
                }
            }
        }

        x += char_width * size;
    }
}
