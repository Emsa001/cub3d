/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:52:35 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 17:12:11 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit_game(1);
}

void destroy_sprite_image(t_sprite *sprite)
{
    int i = 0;
    while(i < sprite->frames){
        printf("trying to destroy frame %d of sprite: %f,%f\n", i, sprite->x, sprite->y);
        if(sprite->sprite_tex[i] == NULL){
            printf("texture is null\n");
            i++;
            continue;
        }
        destroy_texture(sprite->sprite_tex[i]);
        sprite->sprite_tex[i] = NULL;
        i++;
    }

    ft_free(sprite->sprite_tex);
    sprite->sprite_tex = NULL;
}


void destroy_render(){
	t_render *r = render();
    clean_image(r);
	mlx_destroy_window(r->mlx, r->win);
    mlx_destroy_display(r->mlx);
	free(r->mlx);

    pthread_mutex_destroy(&r->image_queue_mutex);
    pthread_mutex_destroy(&r->string_queue_mutex);
}

void	exit_game(int code)
{
    destroy_manager();
    t_textures	*t = textures();
    t_render *r = render();
    t_cube *c = cube();

	t_sprite *sprites = c->map->sprites;
	int i = 0;
	while (sprites[i].x != -1){
        printf("sprite position: %p\n", sprites[i]);
        if(sprites[i].sprite_tex != NULL){
            printf("Destroying sprite type: %c x:%f y:%f\n", sprites[i].type, sprites[i].x, sprites[i].y);
            destroy_sprite_image(&sprites[i]);
        
            sprites[i].sprite_tex = NULL;
        }
        
		i++;
    }

    clear_image_queue(r);
    clear_string_queue(r);
    
    destroy_textures();
    destroy_render();

    ft_destructor();
    exit (code);
}