/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:46:56 by escura            #+#    #+#             */
/*   Updated: 2024/09/24 18:19:50 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Function prototypes
void try_move(float x, float y);
void handle_movement(t_player *p);
void handle_rotation(t_player *p);
void handle_vertical_movement(t_player *p);
void handle_interactions(t_player *p);
void handle_step_animation(t_player *p, bool is_moving);
void handle_jumping(t_player *p);
void update_player_position(t_player *p);
void update_player_direction(t_player *p);
void move_player(void);

// Function implementations
void try_move(float x, float y) {
    const double delta_time = cube()->delta_time;
    t_player *p = player();
    
    int temp_x = p->x_px;
    int temp_y = p->y_px;

    // Update player position
    p->x_px += x * delta_time;
    p->y_px += y * delta_time;

    // Check for collision, revert position if necessary
    if (touch()) 
    {
        p->x_px = temp_x;
        p->y_px = temp_y;
    }
}

void handle_movement(t_player *p) {

    float cos_angle = cos(p->angle);
    float sin_angle = sin(p->angle);
    float left_angle, right_angle;
    bool is_moving = false;

    int speed = p->speed;
    if(p->sprint)
        speed += SPRINTBONUS;

    if (p->btn_w || p->btn_s) { // Forward or backward movement
        if (p->btn_s) { // Move backward
            cos_angle = -cos_angle;
            sin_angle = -sin_angle;
        }
        try_move(0, speed * sin_angle);
        try_move(speed * cos_angle, 0);
        is_moving = true;
    }

    if (p->btn_a) { // Strafe left
        left_angle = p->angle - PI / 2;
        try_move(0, speed * sin(left_angle));
        try_move(speed * cos(left_angle), 0);
        is_moving = true;
    }

    if (p->btn_d) { // Strafe right
        right_angle = p->angle + PI / 2;
        try_move(0, speed * sin(right_angle));
        try_move(speed * cos(right_angle), 0);
        is_moving = true;
    }

    handle_step_animation(p, is_moving);
}

void handle_vertical_movement(t_player *p) {
    if (p->btn_up) // Move up
        p->z += 0.1;

    if (p->btn_down) // Move down
        p->z -= 0.1;
}

void handle_interactions(t_player *p) {
    if (p->interact) { // Door interaction
        int id = get_block_id(cube()->map->doors, p->x, p->y, p->angle);
        if (p->opened)
            close_door(p->angle, id);
        else
            open_door(p->angle, id);
    }

    if (p->spawn) { // Spawn block
        add_block(p->angle);
        p->spawn = false;
    }

    if (p->remove) { // Remove block
        remove_block(p->angle);
        p->remove = false;
    }

    if (p->catch) // Catch block
        catch_block(p->angle);
}

void handle_step_animation(t_player *p, bool is_moving) 
{
    static float step_progress = 0;
    const float step_amplitude = 0.04;
    float step_frequency = 0.2;
    if(p->sprint)
        step_frequency = 0.4;
    const float base_z = 0.55;

    if (is_moving && p->jump_speed == 0) 
    {
        step_progress += step_frequency;
        p->z = base_z + step_amplitude * sin(step_progress);
    } 
    else if (p->jump_speed == 0)
        p->z = base_z;
}


void handle_jumping(t_player *p) 
{
    t_cube *c = cube();
    const float base_z = 0.5;

    if (p->jump_speed > 0) 
    {
        p->z += p->jump_speed * c->delta_time;
        p->jump_speed -= GRAVITY * c->delta_time;
    }
    else if (p->jump_speed < 0)
    {
        p->fall_speed += GRAVITY * c->delta_time;
        p->z -= p->fall_speed * c->delta_time;
        if(p->z <= base_z)
        {
            p->z = base_z;
            p->jump_speed = 0;
            p->fall_speed = 0;
        }
    }
}

void update_player_position(t_player *p) {
    p->x = p->x_px / BLOCK_SIZE;
    p->y = p->y_px / BLOCK_SIZE;
}

void update_player_direction(t_player *p) {
    p->x_dir = cos(p->angle);
    p->y_dir = sin(p->angle);

    p->direction = p->angle * (180 / PI);
    if (p->direction > 180)
        p->direction -= 360;
}

void move_player(void) {
    t_player *p = player();
    if(p->jumping == true && p->z <= 0.6)
    {
        p->jump_speed = JUMP_SPEED;
        p->fall_speed = 0;
    }

    handle_movement(p);
    handle_arrow_rotation(p);
    handle_vertical_movement(p);
    handle_interactions(p);
    handle_jumping(p);
    update_player_position(p);
    update_player_direction(p);
}
