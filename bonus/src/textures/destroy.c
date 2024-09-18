/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:36:08 by escura            #+#    #+#             */
/*   Updated: 2024/09/18 18:38:15 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void destroy_texture(t_texture *texture)
{
    if (texture == NULL || texture->image == NULL || texture->data == NULL)
        return;

    destroy_image(texture->image);
    ft_free(texture->data);
    ft_free(texture);
    
    texture = NULL;
}

void destroy_ui(){
    t_textures *t = textures();
    destroy_texture(t->ui->button);
    destroy_texture(t->ui->button_hover);
    destroy_texture(t->ui->play);
    destroy_texture(t->ui->play_hover);
    destroy_texture(t->ui->window);
    destroy_texture(t->ui->home);
    destroy_texture(t->ui->panel);
}

void destroy_texture_arr(t_texture **t){
    int i = 0;
    while(i < cube()->levels){
        destroy_texture(t[i]);
        i++;
    }
}

void destroy_textures()
{
    printf("Destroying textures\n");
    t_textures	*t = textures();

    destroy_texture_arr(t->wall_north);
    destroy_texture_arr(t->wall_south);
    destroy_texture_arr(t->wall_east);
    destroy_texture_arr(t->wall_west);
    destroy_texture_arr(t->ceiling);
    destroy_texture_arr(t->floor);

    destroy_texture(t->door);
    destroy_texture(t->generator);
    destroy_texture(t->generator1);
    destroy_texture(t->generator_top);
    destroy_texture(t->font);
    destroy_texture(t->inventoryPlayer);
    destroy_texture(t->inventoryGui);
    destroy_texture(t->tooltip_bg);
    destroy_texture(t->open_portal);

    destroy_texture(t->ui->button_long);
    
    destroy_ui();
    
    for (int i = 0; i <= 327; i++) {
        destroy_texture(&(t->items[i]));
    }

    int i = 0;
    while(i < 32){
        destroy_texture(t->ui->keys[i]);
        i++;
    }

    i = 0;
    while(i < 81){
        destroy_texture(t->ui->progress[i]);
        i++;
    }
}