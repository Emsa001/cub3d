/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:18:52 by escura            #+#    #+#             */
/*   Updated: 2024/06/18 19:19:56 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_params(char **av)
{
	if (!av[1] || av[2])
	{
		printf(GREEN "Usage: ./cub3d " BLUE "map.cub\n" RESET);
		exit_game();
	}
}
