/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:36:08 by escura            #+#    #+#             */
/*   Updated: 2024/09/13 20:38:53 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void destroy_texture(t_texture *texture)
{
    if (texture == NULL)
        return;

    // Ensure texture->image is valid before destroying it
    if (texture->image != NULL)
        destroy_image(texture->image);

    // Free the texture data (if it's dynamically allocated)
    if (texture->data != NULL)
        ft_free(texture->data);

    // Free the texture object itself
    ft_free(texture);
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

void destroy_textures()
{
    printf("Destroying textures\n");
    t_textures	*t = textures();

    destroy_texture(t->wall_north);
    destroy_texture(t->wall_south);
    destroy_texture(t->wall_east);
    destroy_texture(t->wall_west);

    destroy_texture(t->door);
    destroy_texture(t->generator);
    destroy_texture(t->generator1);
    destroy_texture(t->generator_top);
    destroy_texture(t->font);
    destroy_texture(t->inventoryPlayer);
    destroy_texture(t->inventoryGui);
    destroy_texture(t->tooltip_bg);
    
    destroy_ui();

    destroy_texture(t->sky);
    destroy_texture(t->floor);
    destroy_texture(t->player);
    
    for (int i = 0; i <= 327; i++) {
        destroy_texture(&t->items[i]);
    }

    int i = 0;
    while(i < 32){
        destroy_texture(t->ui->keys[i]);
        i++;
    }

    i = 0;
    while(i < 2){
        destroy_texture(t->ui->banner[i]);
        i++;
    }

}