/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:40:10 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 19:03:12 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# define WALKSPEED 2
# define SPRINTBONUS 5
# define MOUSE_SENSITIVITY 0.003

# define JUMP_SPEED 0.08
# define JUMP_HEIGHT 0.9

# define FOV 60

typedef struct s_player
{
	float	x;
	float	y;
	float	z;

	float	x_px;
	float	y_px;

	float	x_dir;
	float	y_dir;
	float	z_dir;

	float	angle;
	double	direction;

	bool	btn_w;
	bool	btn_s;
	bool	btn_a;
	bool	btn_d;

	bool	btn_up;
	bool	btn_down;
	bool	btn_left;
	bool	btn_right;
	bool	pause;
	bool	interact;
	bool	opened;

	bool	spawn;
	bool	remove;

	bool	catch;
	bool	catched;

	float	jump_height;

	int		fov;

	int		speed;
	bool	sprint;

	float	plane_x;
	float	plane_y;

	int		health;

	bool	mouse_hook;
	bool	open_inventory;

	int 	inventory[9];
	int 	equipped[8];

	bool 	vision;

	t_item 	*cursorItem;
	t_item 	*hand;
	bool 	swing;
}			t_player;

t_player	*player_init(t_player *p);
t_player	*player(void);
void		move_player(void);
void		jump_player(void);
bool		touch(void);
void		render_player(void);
void		handle_mouse_rotate(int x, int y);
void		handle_arrow_rotation(t_player *p);
void		open_inventory(void);

int			view_lane_distance(float x1, float y1, float angle);

void		player_keydown(int keycode);
void		player_keyup(int keycode);
void		player_mouseclick(int button);

#endif
