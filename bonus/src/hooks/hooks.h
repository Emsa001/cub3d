/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:34:44 by escura            #+#    #+#             */
/*   Updated: 2024/08/02 20:37:49 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "cub3d.h"

/* KeyBoard */

int key_down(int keycode);
int key_up(int keycode);


/* Mouse */
int mouse_click(int button);
int mouse_move(int x, int y);

#endif