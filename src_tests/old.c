// void interpolate_pixels()
// {
//     t_render *r = render(NULL);

//     r->img_ptr = mlx_new_image(mlx, WIDTH, HEIGHT);
//     r->img_data = mlx_get_data_addr(r->img_ptr, &r->bits_per_pixel, &r->size_line, &r->endian);

//     for (int y = 0; y < HEIGHT; y++)
//     {
//         for (int x = 0; x < WIDTH; x++)
//         {
//             int src_x = (x - (WIDTH / 2 - (scaled_img_width * RES_DOWNGRADE) / 2)) / RES_DOWNGRADE;
//             int src_y = ((HEIGHT / 2 + (scaled_img_height * RES_DOWNGRADE) / 2) - y) / RES_DOWNGRADE;

//             if (src_x >= 0 && src_x < scaled_img_width && src_y >= 0 && src_y < scaled_img_height)
//             {
//                 int color = get_pixel_from_image(scaled_data_addr, scaled_img_width, scaled_img_height, (int)src_x, (int)src_y, scaled_size_line, scaled_bpp);
//                 insert_pixel(x, y, color);
//             }
//         }
//     }
// }

// void scale_image()
// {
//     // Calculate the new width and height of the scaled image
//     scaled_img_width = (int)(img_width * scale_factor / RES_DOWNGRADE);
//     scaled_img_height = (int)(img_height * scale_factor / RES_DOWNGRADE);

//     // Check if the scaled image has been created
//     if (!scaled_img)
//     {
//         // Create a new image with the maximum possible dimensions
//         scaled_img = mlx_new_image(mlx, WIDTH, HEIGHT);
//         scaled_data_addr = mlx_get_data_addr(scaled_img, &scaled_bpp, &scaled_size_line, &scaled_endian);
//     }

//     // Calculate the ratio for scaling the resolution
//     double res_scale_ratio = RES_DOWNGRADE / scale_factor;
//     int scaled_bpp_div_8 = scaled_bpp / 8;

//     int width = WIDTH >= scaled_img_width ? scaled_img_width : WIDTH;
//     int height = HEIGHT >= scaled_img_height ? scaled_img_height : HEIGHT;

//     // Iterate over the dimensions of the scaled image
//     for (int y = 0;y < height; y++)
//     {
//         for (int x = 0 ;x < width; x++)
//         {
//             // Map the coordinates to the original image dimensions
//             int orig_x = (int)(x * res_scale_ratio);
//             int orig_y = (int)(y * res_scale_ratio);

//             // Ensure the mapped coordinates are within the original image bounds
//             if (orig_x >= 0 && orig_x < img_width && orig_y >= 0 && orig_y < img_height)
//             {
//                 // Retrieve the color from the original image
//                 int color = get_pixel_from_image(data_addr, img_width, img_height, orig_x, orig_y, size_line, bpp);

//                 // Calculate the position in the scaled image and set the pixel color
//                 char *pixel = scaled_data_addr + (y * scaled_size_line + x * scaled_bpp_div_8);
//                 *(int *)pixel = color;
//             }
//         }
//     }

//     // Interpolate pixels if needed
//     interpolate_pixels();
// }