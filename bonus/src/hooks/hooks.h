/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:34:44 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 21:58:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"
#ifndef HOOKS_H
# define HOOKS_H


/* KeyBoard */

int key_down(int keycode);
int key_up(int keycode);


/* Mouse */
int mouse_click(int button);
int mouse_move(int x, int y);

#endif