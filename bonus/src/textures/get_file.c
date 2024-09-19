/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:06:58 by escura            #+#    #+#             */
/*   Updated: 2024/09/19 16:13:02 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*get_texture_file(char *file, int *width, int *height)
{
	void	*image;

	if (!file || open(file, O_RDONLY) < 0){
		printf("Error\nInvalid texture file: %s\n", file);
		exit_game(1);
	}
	image = mlx_xpm_file_to_image(render()->mlx, file, width, height);
	return (image);
}
