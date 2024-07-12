/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:18:52 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 17:14:41 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_params(char **av)
{
	if (!av[1] || av[2])
	{
		printf(GREEN "Usage: ./cub3d " BLUE "map.cub\n" RESET);
		exit_game();
	}
}
