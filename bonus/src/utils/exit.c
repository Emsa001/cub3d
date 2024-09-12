/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:52:35 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 21:59:27 by escura           ###   ########.fr       */
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
    while(i < sprite.frames){
        destroy_texture(sprite.sprite_tex[i]);
        i++;
    }
}

void destroy_render(){
	t_render *r = render();
	mlx_destroy_window(r->mlx, r->win);
	free(r->mlx);
}

void	exit_game(int code)
{
    t_textures	*t = textures();
    t_render *r = render();
    t_cube *c = cube();

    stop_all_async_tasks();
    sleep(1);

    destroy_textures();

	t_sprite *sprites = c->map->sprites;
	int i = 0;
	while (sprites[i].x != -1){
        destroy_sprite_image(sprites[i]);
		i++;
    }

    destroy_render();
    // ft_destructor();
    exit (1);
}