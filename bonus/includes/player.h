/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:40:10 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 14:20:34 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"
# include "economy.h"
typedef struct s_draw		t_draw;

# define WALKSPEED 2
# define SPRINTBONUS 5
# define MOUSE_SENSITIVITY 0.003

# define JUMP_SPEED 0.08
# define JUMP_HEIGHT 0.38

# define FOV 60

typedef struct s_button
{
	int						x;
	int						y;
	int						width;
	int						height;

	void					(*function)(void *);
	void					(*hover)(void *);
	void					*arg;
	int						itemId;

}							t_button;

typedef struct s_button_node
{
	t_button				button;
	struct s_button_node	*next;
}							t_button_node;

typedef struct s_player
{
	float					x;
	float					y;
	float					z;

	float					x_px;
	float					y_px;

	float					x_dir;
	float					y_dir;
	float					z_dir;

	float					angle;
	double					direction;

	bool					btn_w;
	bool					btn_s;
	bool					btn_a;
	bool					btn_d;

	bool					btn_up;
	bool					btn_down;
	bool					btn_left;
	bool					btn_right;
	bool					pause;
	bool					interact;
	bool					opened;

	bool					spawn;
	bool					remove;

	bool					catch;
	bool					catched;

	float					jump_height;

	int						fov;

	int						speed;
	bool					sprint;

	float					plane_x;
	float					plane_y;

	bool					mouse_hook;
	bool					open_inventory;

	int						inventory[9];
	int						equipped[8];

	bool					vision;
	int						money;
	pthread_mutex_t			money_mutex;

	t_button				*hover;
	t_item					*hand;
	bool					swing;
	t_store					*store;
}							t_player;

t_player					*player_init(t_player *p);
t_player					*player(void);
void						move_player(void);
void						jump_player(void);
bool						touch(void);
void						render_player(void);
void						handle_mouse_rotate(int x, int y);
void						handle_arrow_rotation(t_player *p);
void						open_inventory(void);

void						lane_distance(t_draw *draw);

void						player_keydown(int keycode);
void						player_keyup(int keycode);
void						player_mouseclick(int button);
void						pause_game(void);
void						render_ui(void);

void						tooltip(char *string, float size);
void						hud_currency(void);
t_store						*init_store(void);
void						open_store(void);
float						distance(float x1, float y1, float x2, float y2);
void	hud_inventory(void);

#endif
