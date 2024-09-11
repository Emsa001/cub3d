/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   economy.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:18:44 by escura            #+#    #+#             */
/*   Updated: 2024/09/11 17:44:16 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECONOMY_H
# define ECONOMY_H

# include "cub3d.h"

typedef struct s_store{

	int x;
	int y;

    bool can_open;
	bool open;
	int items[27];
	int cases[3];
	int generators[2];

} t_store;

#endif
