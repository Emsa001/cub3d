/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:53 by escura            #+#    #+#             */
/*   Updated: 2024/07/17 20:43:24 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_block *get_all_possible_blocks(int x, int y)
{
    t_block *possible = ft_malloc(sizeof(t_block) * 12);
    possible[0].x = x + 2;
    possible[0].y = y;
    possible[1].x = x + 2;
    possible[1].y = y + 1;
    possible[2].x = x + 1;
    possible[2].y = y + 2;
    possible[3].x = x;
    possible[3].y = y + 2;
    possible[4].x = x - 1;
    possible[4].y = y + 2;
    possible[5].x = x - 2;
    possible[5].y = y + 1;
    possible[6].x = x - 2;
    possible[6].y = y;
    possible[7].x = x - 2;
    possible[7].y = y - 1;
    possible[8].x = x - 1;
    possible[8].y = y - 2;
    possible[9].x = x;
    possible[9].y = y - 2;
    possible[10].x = x + 1;
    possible[10].y = y - 2;
    possible[11].x = x + 2;
    possible[11].y = y - 1;
    return possible;
}

void get_currect_block(t_block *possible, float ray_angle, int *x, int *y)
{
    if(ray_angle >= 345 || ray_angle < 15)
    {
        *x = possible[0].x;
        *y = possible[0].y;
    }
    else if(ray_angle >= 15 && ray_angle < 45)
    {
        *x = possible[1].x;
        *y = possible[1].y;
    }
    else if(ray_angle >= 45 && ray_angle < 75)
    {
        *x = possible[2].x;
        *y = possible[2].y;
    }
    else if(ray_angle >= 75 && ray_angle < 105)
    {
        *x = possible[3].x;
        *y = possible[3].y;
    }
    else if(ray_angle >= 105 && ray_angle < 135)
    {
        *x = possible[4].x;
        *y = possible[4].y;
    }
    else if(ray_angle >= 135 && ray_angle < 165)
    {
        *x = possible[5].x;
        *y = possible[5].y;
    }
    else if(ray_angle >= 165 && ray_angle < 195)
    {
        *x = possible[6].x;
        *y = possible[6].y;
    }
    else if(ray_angle >= 195 && ray_angle < 225)
    {
        *x = possible[7].x;
        *y = possible[7].y;
    }
    else if(ray_angle >= 225 && ray_angle < 255)
    {
        *x = possible[8].x;
        *y = possible[8].y;
    }
    else if(ray_angle >= 255 && ray_angle < 285)
    {
        *x = possible[9].x;
        *y = possible[9].y;
    }
    else if(ray_angle >= 285 && ray_angle < 315)
    {
        *x = possible[10].x;
        *y = possible[10].y;
    }
    else if(ray_angle >= 315 && ray_angle < 345)
    {
        *x = possible[11].x;
        *y = possible[11].y;
    }
}

void spawn_block(float angle, int i)
{
    t_player *p = player();
    t_cube *c = cube();
    t_map *map = c->map;
    t_block *possible;

    
    int x = 0;
    int y = 0;

    angle = angle * (180 / PI);
    
    possible = get_all_possible_blocks(p->x, p->y);

    get_currect_block(possible, angle, &x, &y);
    
    if(i == 1)
    {
        if(map->map[y][x] == '0')
        {
            map->map[y][x] = '2';
            c->map->blocks = init_block(map, '2');
        }
        else
            printf("Can't spawn block here \n");
    }
    else
    {
        if(map->map[y][x] == '2')
        {
            map->map[y][x] = '0';
            c->map->blocks = init_block(map, '2');
        }
        else
            printf("Can't remove block here \n");
    }
    ft_free(possible);
}

void open_door(void)
{
    t_player *p = player();
    t_cube *c = cube();
    t_block *doors = c->map->doors;
    static int open;
    
    if(doors[0].y >= doors[0].first_y - 0.9 && doors[0].y == doors[0].first_y)
            open = 1;
    else if(doors[0].y <= doors[0].first_y && doors[0].y <= doors[0].first_y - 0.9)
            open = 0;

    if(open == 1)
        doors[0].y = doors[0].y - 0.05;
    else
        doors[0].y = doors[0].y + 0.05;

    p->interact = false;
}

void	try_move(float x, float y)
{
	const t_cube	*c = cube();
	t_player		*p;
	int				temp_x;
	int				temp_y;

	p = player();
	temp_x = p->x_px;
	temp_y = p->y_px;
	p->x_px += x;
	p->y_px += y;
	if (touch(WALL))
	{
		p->x_px -= x;
		p->y_px -= y;
	}
}

void move_player(void) {
    t_player *p = player();
    float cos_angle = cos(p->angle);
    float sin_angle = sin(p->angle);
    float left_angle, right_angle;

    if (p->btn_w || p->btn_s) {
        if (p->btn_s) {
            cos_angle = -cos_angle;
            sin_angle = -sin_angle;
        }
        try_move(0, p->speed * sin_angle);
        try_move(p->speed * cos_angle, 0);
    }
    if (p->btn_a) {
        left_angle = p->angle - PI / 2;
        try_move(0, p->speed * sin(left_angle));
        try_move(p->speed * cos(left_angle), 0);
    }
    if (p->btn_d) {
        right_angle = p->angle + PI / 2;
        try_move(0, p->speed * sin(right_angle));
        try_move(p->speed * cos(right_angle), 0);
    }
    if (p->btn_left) {
        p->angle -= 0.1;
        if (p->angle < 0)
            p->angle += 2 * PI;
    }
    if (p->btn_right) {
        p->angle += 0.1;
        if (p->angle > 2 * PI)
            p->angle -= 2 * PI;
    }

    if(p->btn_up)
    {
        p->z_dir += 0.1;
        if(p->z_dir > 2)
            p->z_dir = 2;
    }
    if(p->btn_down)
    {
        p->z_dir -= 0.1;
        if(p->z_dir < -2)
            p->z_dir = -2;
    }

    if(p->interact)
        open_door();

    if(p->spawn)
    {
        spawn_block(p->angle, 1);
        p->spawn = false;
    }
    if(p->remove)
    {
        spawn_block(p->angle, 0);
        p->remove = false;
    }

    p->x = p->x_px / BLOCK_SIZE;
    p->y = p->y_px / BLOCK_SIZE;

    // Update direction vectors based on angle
    p->x_dir = cos(p->angle);
    p->y_dir = sin(p->angle);

    p->direction = p->angle * (180 / PI);
    if (p->direction > 180)
        p->direction -= 360;
    
    // printf("\n");
    // printf("direction: %f\n", p->direction);
    // printf("angle: %f\n", p->angle);
    // printf("x_dir: %f\n", p->x_dir);
    // printf("y_dir: %f\n", p->y_dir);
    // printf("x: %f\n", p->x);
    // printf("y: %f\n", p->y);
    // printf("\n");

    // float tmp_x = p->plane_x;
    // p->plane_x = p->plane_x * cos(p->speed) - p->plane_y * sin(p->speed);
	// p->plane_y = tmp_x * sin(p->speed) + p->plane_y * cos(p->speed);
}


bool	touch(char c)
{
	const int	x = player()->x_px;
	const int	y = player()->y_px;
	const char	**map = cube()->map->map;

    if(is_touching(x - 10, y - 10, c) || is_touching(x + 10, y - 10, c) || is_touching(x - 10, y + 10, c) || is_touching(x + 10, y + 10, c))
        return (true);
    if(touch_block(x - 10, y - 10, DOOR) || touch_block(x + 10, y - 10, DOOR) || touch_block(x - 10, y + 10, DOOR) || touch_block(x + 10, y + 10, DOOR)) 
        return (true);
    if(touch_block(x - 10, y - 10, BLOCK) || touch_block(x + 10, y - 10, BLOCK) || touch_block(x - 10, y + 10, BLOCK) || touch_block(x + 10, y + 10, BLOCK)) 
        return (true);
    
	return (false);
}
