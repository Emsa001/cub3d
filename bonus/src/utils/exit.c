/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:52:35 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 17:22:58 by btvildia         ###   ########.fr       */
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

void destroy_sprite_image(t_sprite sprite)
{
    int i = 0;
    while(i < sprite.frames)
    {
        destroy_texture(sprite.sprite_tex[i]);
        sprite.sprite_tex[i] = NULL;
        i++;
    }
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
	while (sprites[i].x != -1)
    {
        if(sprites[i].sprite_tex != NULL)
            destroy_sprite_image(sprites[i]);
		i++;
    }

    clear_image_queue(r);
    clear_string_queue(r);
    
    destroy_textures();
    destroy_render();

    ft_destructor();
    exit (code);
}