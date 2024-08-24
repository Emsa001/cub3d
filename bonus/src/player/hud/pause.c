#include "cub3d.h"

void pause_game(void)
{
    t_render *r = render();
    t_cube *c = cube();
    
    r->img_ptr = mlx_new_image(r->mlx, WIDTH, HEIGHT);
    
    mlx_put_image_to_window(r->mlx, r->win, r->img_ptr , 0, 0);
    mlx_destroy_image(r->mlx, r->img_ptr);
    
}