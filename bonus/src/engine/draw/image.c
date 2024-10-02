/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:35:54 by escura            #+#    #+#             */
/*   Updated: 2024/10/01 16:43:31 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void remove_image_queue(t_image **q)
{
    if (*q)
    {
        if ((*q)->img)
            (*q)->img = NULL;
        free(*q);
        *q = NULL;
    }
}

void clear_image_queue(t_render *r)
{
    printf("Clearing image queue\n");
    pthread_mutex_lock(&r->image_queue_mutex);

    t_image *current = r->image_queue;
    t_image *next = NULL;

    while (current != NULL)
    {
        next = current->next;    // Save the next pointer
        remove_image_queue(&current);  // Free the current image
        current = next;          // Move to the next image
    }

    r->image_queue = NULL;  // Set the queue to NULL

    pthread_mutex_unlock(&r->image_queue_mutex);
}


void put_image_queue(t_render *r)
{
    pthread_mutex_lock(&r->image_queue_mutex);

    t_image *q = r->image_queue;
    while (q != NULL)
    {
        put_image(q->img, q->x, q->y, q->size);

        t_image *tmp = q->next;
        remove_image_queue(&q);
        q = tmp;
    }

    r->image_queue = NULL;

    pthread_mutex_unlock(&r->image_queue_mutex);
}



void enqueue_image(t_async *async)
{
    t_image *img = (t_image *)async->arg;
    t_render *r = render();
    t_image *new = calloc(1, sizeof(t_image));

    if (!new)
    {
        perror("Failed to allocate memory for new image");
        return;
    }

    // Copying the image data
    new->img = img->img;  // Assuming img->img is a pointer to texture data
    new->x = img->x;
    new->y = img->y;
    new->size = img->size;
    new->time = img->time;
    new->next = NULL;

    pthread_mutex_lock(&r->image_queue_mutex);

    if (!r->image_queue)
        r->image_queue = new;
    else
    {
        t_image *q = r->image_queue;
        while (q->next)
            q = q->next;
        q->next = new;
    }

    pthread_mutex_unlock(&r->image_queue_mutex);

}

void end_image(t_async *async)
{
    t_image *img = (t_image *)async->arg;
    if (img)
    {
        if (img->img)
            img->img = NULL;
        ft_free(img);
    }
}

void render_image_async(t_image *img)
{
    t_async *async = new_async();
    t_image *img_copy = ft_malloc(sizeof(t_image));

    // Deep copy the image data
    img_copy->img = img->img;  // Assuming img->img is a pointer to texture data
    img_copy->x = img->x;
    img_copy->y = img->y;
    img_copy->size = img->size;
    img_copy->time = img->time;
    img_copy->next = NULL;

    async->process = &enqueue_image;
    async->end = &end_image;
    async->arg = img_copy;
    async->process_time = 5;
    async->time = img->time;
    start_async(async);
}


void put_image(t_texture *img, int x, int y, float size)
{
    t_render *r = render();
    if (!r->img_ptr || !img)
        return;

    for (int i = 0; i < img->width; ++i)
    {
        for (int j = 0; j < img->height; ++j)
        {
            int color = get_pixel_from_image(img, i, j);
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
        }
    }
}


void change_image_color(t_texture *img, int color)
{
    if (!img)
        return;

    for (int i = 0; i < img->width; ++i)
    {
        for (int j = 0; j < img->height; ++j)
        {
            int index = j * img->size_line + i * img->bpp / 8;
            img->data[index] = color & 0xFF;              // Blue
            img->data[index + 1] = (color >> 8) & 0xFF;   // Green
            img->data[index + 2] = (color >> 16) & 0xFF;  // Red
        }
    }
}
