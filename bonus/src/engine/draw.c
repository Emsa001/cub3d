/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:40:03 by escura            #+#    #+#             */
/*   Updated: 2024/07/21 18:58:02 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int side = 6;

int calculate_direction(float x, float y, float angle)
{
	int sx = cos(angle) > 0 ? 1 : -1; 
	int sy = sin(angle) > 0 ? 1 : -1;
	t_cube *c = cube();

	if(is_touching(x - sx, y))
	{
		c->tex_x = (int)x % BLOCK_SIZE;
		if (sy == 1)
			return 1;
		else
			return 3;
	}
	else if(is_touching(x, y - sy))
	{
		c->tex_x = (int)y % BLOCK_SIZE;
		if (sx == 1)
			return 2;
		else
			return 4;
	}
	else if(touch_block(c->map->doors, x - sx, y))
	{
		c->tex_x = (int)x % BLOCK_SIZE;
		return 5;
	}
	else if(touch_block(c->map->doors, x , y - sy))
	{
		c->tex_x = (int)y % BLOCK_SIZE;
		return 5;
	}
	else if(touch_block(c->map->blocks, x - sx, y))
	{
		c->tex_x = (int)x % BLOCK_SIZE;
		return 6;
	}
	else if(touch_block(c->map->blocks, x, y - sy))
	{
		c->tex_x = (int)y % BLOCK_SIZE;
		return 6;
	}
	return 6;
}

int vert_offset()
{
	t_player *p = player();
	float z_dir = p->z_dir;
	return (z_dir) * HEIGHT;
}

static t_texture *get_wall_side(int side){
	t_texture *t = NULL;

	if(side == 1)
		t = textures()->wall_north;
	else if(side == 2)
		t = textures()->wall_south;
	else if(side == 3)
		t = textures()->wall_east;
	else if(side == 4)
		t = textures()->wall_west;
	else if(side == 5)
		t = textures()->door;
	else if(side == 6)
		t = textures()->wall_west;
	
	return t;
}

void draw_h_line(float height, int start_x)
{
    const t_cube *c = cube();
	
    int color = 0;
	float tex_y = 0;
    int end;
	int start_y = 0;
	
	float step = T_SIZE / height;

	//TODO: - doesn't work properly
	if(height > HEIGHT)
	{
		tex_y = ((height - HEIGHT) * step / 2);
		height = HEIGHT;
	}
	
    start_y = (player()->z * height + vert_offset());
	end = start_y + height;
	
    while (start_y < end)
    {
		if(player()->catch && side == 6)
			color = 255;
		else
			color = get_pixel_from_image(get_wall_side(side), c->tex_x, tex_y);
        put_pixel(start_x , start_y, color);
		tex_y += step;
        start_y++;
    }
}

bool find_hitbox(float x, float y)
{
	if(is_touching(x, y))
		return false;
	if(touch_block(cube()->map->blocks, x, y))
		return false;
	if(touch_block(cube()->map->doors, x, y))
		return false;

	return true;
}

void	draw_line(float angle , int start_x)
{
	t_player *p = player();
	float x = p->x_px;
	float y = p->y_px;
	float dist = 0;
	float line_height = 0;
	
	while(find_hitbox(x,y))
	{
		x += cos(angle);
		y += sin(angle);
	}

	side = calculate_direction(x, y, angle);

	dist = view_lane_distance(x, y, angle);
	line_height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	draw_h_line(line_height, start_x);
}

void render_view()
{
	t_cube *c = cube();

	float angle = player()->angle;
	int i = 0;

	float fovInRadians = player()->fov * PI / 180;
	float halfFovInRadians = fovInRadians / 2.0;
	float angleOffset = angle - halfFovInRadians;

	while (i < WIDTH)
    {
		float fraction = (float)i / WIDTH;
		float rayAngle = angleOffset + fraction * fovInRadians;
		draw_line(rayAngle, i);
		i++;
	}
}

void put_pixel_to_image(t_texture *texture, int x, int y, int color) {
    if (x >= 0 && x < texture->width && y >= 0 && y < texture->height) {
        char *pixel = texture->data + (y * texture->size_line + x * (texture->bpp / 8));
        *(int *)pixel = color;
    }
}

t_texture *rotate_image(t_texture *original, float angle) {
    t_texture *rotated = malloc(sizeof(t_texture));
    rotated->width = original->width;
    rotated->height = original->height;
    rotated->bpp = original->bpp;
    rotated->size_line = original->size_line;
    rotated->data = malloc(rotated->size_line * rotated->height);
    memset(rotated->data, 0, rotated->size_line * rotated->height); // Initialize with zeros

    float cos_angle = cos(angle);
    float sin_angle = sin(angle);

    int x_center = original->width / 2;
    int y_center = original->height / 2;

    for (int y = 0; y < rotated->height; y++) {
        for (int x = 0; x < rotated->width; x++) {
            int src_x = (int)((x - x_center) * cos_angle + (y - y_center) * sin_angle + x_center);
            int src_y = (int)(-(x - x_center) * sin_angle + (y - y_center) * cos_angle + y_center);

            if (src_x >= 0 && src_x < original->width && src_y >= 0 && src_y < original->height) {
                int color = get_pixel_from_image(original, src_x, src_y);
                put_pixel_to_image(rotated, x, y, color);
            }
        }
    }
    return rotated;
}

void draw_texture(t_texture *texture, int x_pos, int y_pos)
{
    for (int y = 0; y < texture->height; y++)
    {
        for (int x = 0; x < texture->width; x++)
        {
            int color = get_pixel_from_image(texture, x, y);
			if(color >= 0)
            	put_pixel(x_pos + x, y_pos + y, color);
        }
    }
}