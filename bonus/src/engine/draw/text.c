/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:34:36 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 18:58:32 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void dequeue_string(t_string **q)
{
    t_string *tmp = (*q)->next;
    ft_free((*q)->str);
    ft_free(*q);
    *q = tmp;
}

void free_string_arg(t_async *async){
    t_string *str = (t_string *)async->arg;
    ft_free(str->str);
    ft_free(str);
}

void enqueue_string(t_async *async) {
    t_string *text = (t_string *)async->arg;
    t_render *r = render();
    t_string *new = ft_malloc(sizeof(t_string));
    new->str = ft_strdup(text->str);
    new->x = text->x;
    new->y = text->y;
    new->color = text->color;
    new->size = text->size;
    new->next = NULL;

    pthread_mutex_lock(&r->string_queue_mutex);  // Lock the mutex before accessing the queue

    if (r->string_queue == NULL) {
        r->string_queue = new;
    } else {
        t_string *q = r->string_queue;
        while (q->next != NULL)
            q = q->next;
        q->next = new;
    }

    pthread_mutex_unlock(&r->string_queue_mutex);  // Unlock the mutex after modifying the queue
}

void render_string_async(t_string *str)
{
    t_string *copy = ft_calloc(sizeof(t_string), 1);
    ft_memcpy(copy, str, sizeof(t_string));

    t_async *async = (t_async *)ft_calloc(sizeof(t_async), 1);
    async->process = &enqueue_string;
    async->arg = copy;
    async->process_time = 10;
    async->time = str->time;
    add_async(async);
}

void process_string_queue() {
    t_render *r = render();
    pthread_mutex_lock(&r->string_queue_mutex);  // Lock the mutex before accessing the queue

    t_string *q = r->string_queue;
    while (q != NULL) {
        render_string(q);

        t_string *tmp = q->next;
        dequeue_string(&q);
        q = tmp;
    }

    r->string_queue = NULL;
    pthread_mutex_unlock(&r->string_queue_mutex);  // Unlock the mutex after modifying the queue
}


// https://stmn.itch.io/font2bitmap
void render_string(t_string *string)
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

    char *str = string->str;
    int x = string->x;
    int y = string->y;
    int color = string->color;
    float size = string->size;

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
