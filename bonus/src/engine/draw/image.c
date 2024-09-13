/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:35:54 by escura            #+#    #+#             */
/*   Updated: 2024/09/13 20:24:36 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void remove_image_queue(t_image **q)
{
    t_image *tmp = (*q)->next;
    ft_free(*q);
    *q = tmp;
}

void add_image_queue(t_texture *img, int x, int y, float size, t_render *r)
{
    t_image *new = ft_malloc(sizeof(t_image));

    new->img = img;
    new->x = x;
    new->y = y;
    new->size = size;
    new->next = NULL;

    pthread_mutex_lock(&r->image_queue_mutex);  // Lock the mutex before accessing the queue

    if (r->image_queue == NULL)
    {
        r->image_queue = new;
    }
    else
    {
        t_image *q = r->image_queue;
        while (q->next != NULL)
            q = q->next;
        q->next = new;
    }

    pthread_mutex_unlock(&r->image_queue_mutex);  // Unlock the mutex after modifying the queue
}


void put_image_queue(t_render *r)
{
    pthread_mutex_lock(&r->image_queue_mutex);  // Lock the mutex before accessing the queue

    t_image *q = r->image_queue;
    while (q != NULL)
    {
        put_image(q->img, q->x, q->y, q->size);
        
        t_image *tmp = q->next;
        remove_image_queue(&q);
        q = tmp;
    }

    r->image_queue = NULL;

    pthread_mutex_unlock(&r->image_queue_mutex);  // Unlock the mutex after modifying the queue
}

void enqueue_image(t_async *async) {
    t_image *img = (t_image *)async->arg;
    t_render *r = render();
    t_image *new = ft_malloc(sizeof(t_image));
    ft_memcpy(new, img, sizeof(t_image));
    new->next = NULL;

    pthread_mutex_lock(&r->image_queue_mutex);  // Lock the mutex before accessing the queue

    if (r->image_queue == NULL)
        r->image_queue = new;
    else
    {
        t_image *q = r->image_queue;
        while (q->next != NULL)
            q = q->next;
        q->next = new;
    }

    pthread_mutex_unlock(&r->image_queue_mutex);  // Unlock the mutex after modifying the queue
}

void render_image_async(t_image *img)
{
    t_image *copy = ft_calloc(sizeof(t_image), 1);
    ft_memcpy(copy, img, sizeof(t_image));

    t_async *async = new_async();
    async->process = &enqueue_image;
    async->end = NULL;
    async->arg = copy;
    async->process_time = 10;
    async->time = img->time;
    start_async(async);

}

void put_image(t_texture *img, int x, int y, float size)
{
    t_render *r = render();
    int i = 0;
    int j = 0;
    int color = 0;

    if(r->img_ptr == NULL)
        return;

    // Iterate over each pixel in the original image
    while (i < img->width)
    {
        j = 0;
        while (j < img->height)
        {
            color = get_pixel_from_image(img, i, j);

            if (color && color > 0)
            {
                for (int dx = 0; dx < size; ++dx)
                {
                    for (int dy = 0; dy < size; ++dy)
                    {
                        put_pixel(x + i * size + dx, y + j * size + dy, color, r);
                    }
                }
            }

            j++;
        }
        i++;
    }
}

void change_image_color(t_texture *img, int color)
{
    int i = 0;
    int j = 0;

    while (i < img->width)
    {
        j = 0;
        while (j < img->height)
        {
            int index = j * img->size_line + i * img->bpp / 8;
            img->data[index] = color & 0xFF;              // Blue component
            img->data[index + 1] = (color >> 8) & 0xFF;   // Green component
            img->data[index + 2] = (color >> 16) & 0xFF;  // Red component
            j++;
        }
        i++;
    }
}