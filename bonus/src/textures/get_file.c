/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:06:58 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 21:52:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "textures.h"

void *get_texture_file(char *file, int *width, int *height)
{
    if(!file || open(file, O_RDONLY) < 0)
        ft_error("Error\nInvalid texture file\n");

    void *image = mlx_xpm_file_to_image(render()->mlx, file, width, height);
    return (image);
}