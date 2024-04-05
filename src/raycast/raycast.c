#include "cub3d.h"

int keys(int key, void *param)
{
	t_main_data *data = (t_main_data *)param;
	if (key == 'a')
	{
		data->player.x -=5;
	}
	if (key == 'd')
		data->player.x +=5;
	if (key == 'w')
		data->player.y -=5;
	if (key == 's')
		data->player.y +=5;
	if (key == 65361) // Left
	{
    	data->player.angle -= 0.1;
    	if (data->player.angle < 0)
			data->player.angle += 2 * PI;
    	data->player.dx = cos(data->player.angle) * 5;
    	data->player.dy = sin(data->player.angle) * 5;
	}
	if (key == 65363) // Right
	{
    	data->player.angle += 0.1;
    	if (data->player.angle >= 2 * PI)
			data->player.angle -= 2 * PI;
    	data->player.dx = cos(data->player.angle) * 5;
    	data->player.dy = sin(data->player.angle) * 5;
	}
	return 0;
}

void	draw_map(t_main_data *data, int *addr)
{
	int i = 0;
	int j;
	int color;
    while (i < data->map.height)
	{
		j = 0;
        while (j < data->map.width)
		{
            int tile = data->map.tiles[i * data->map.width + j];
            if (tile == 1)
				color = 0xFFFFFF;
			else 
				color = 0x000000;
			int y = 0;

            while (y < data->map.size)
			{
				int x = 0;
                while (x < data->map.size)
				{
                    int pixel_index = ((i * data->map.size + y) * data->w.width + (j * data->map.size + x));
					// Checking Bounds
					if (pixel_index >= 0 && pixel_index < data->w.width * data->w.height)
    					addr[pixel_index] = color;
					x++;
                }
				y++;
            }
			j++;
        }
		i++;
    }
}

void draw_grid_lines(t_main_data *data, int *addr)
{
    int lineColor = 0xC0C0C0FF; // Light gray for grid lines.
    int mapPixelWidth = data->map.width * data->map.size;
    int mapPixelHeight = data->map.height * data->map.size;

    // Draw horizontal lines within the map
    int y = 0;
    while (y <= mapPixelHeight) { // Use <= to include the last line at the map's bottom edge
        int x = 0;
        while (x < mapPixelWidth) { // Draw line across the map's width
            int pixel_index = (y * data->w.width) + x;
            if (pixel_index < data->w.width * data->w.height) {
                addr[pixel_index] = lineColor;
            }
            x++;
        }
        y += data->map.size; // Increment y by the size of one map tile
    }

    // Draw vertical lines within the map
    int x = 0;
    while (x <= mapPixelWidth) { // Use <= to include the last line at the map's right edge
        y = 0;
        while (y < mapPixelHeight) { // Draw line down the map's height
            int pixel_index = (y * data->w.width) + x;
            if (pixel_index < data->w.width * data->w.height) {
                addr[pixel_index] = lineColor;
            }
            y++;
        }
        x += data->map.size; // Increment x by the size of one map tile
    }
}

void draw_player(t_main_data *data, int *addr)
{
	int y = 0;
    while (y < data->player.size)
	{
		int x = 0;
		while (x < data->player.size)
		{
            int pixel_index = ((data->player.y + y) * data->w.width + (data->player.x + x));
            if (pixel_index < data->w.width * data->w.height)
			{
                addr[pixel_index] = data->player.color;
            }
			x++;
        }
		y++;
    }
}

void draw_line_on_image(int *addr, int width, int height, int start_x, int start_y, int end_x, int end_y, int color) {
    int delta_x = abs(end_x - start_x), step_x = start_x < end_x ? 1 : -1;
    int delta_y = -abs(end_y - start_y), step_y = start_y < end_y ? 1 : -1; 
    int error = delta_x + delta_y, error2; // error value e_xy
    
    while (1) {  // The loop will run until break is called
        if (start_x >= 0 && start_x < width && start_y >= 0 && start_y < height) {
            addr[start_y * width + start_x] = color; // Draw pixel
        }
        
        if (start_x == end_x && start_y == end_y) break; // Line has been drawn
        
        error2 = 2 * error;
        if (error2 >= delta_y) { // e_xy+e_x > 0
            if (start_x == end_x) break;
            error += delta_y;
            start_x += step_x;
        }
        if (error2 <= delta_x) { // e_xy+e_y < 0
            if (start_y == end_y) break;
            error += delta_x;
            start_y += step_y;
        }
    }
}

/*
void draw_vertical_rays(t_main_data *data, int *addr)
{
    int map_x, map_y, map_pos, depth;
    float ray_x, ray_y, ray_angle, step_x, step_y;

    ray_angle = data->player.angle;
	
	int r = 0;
	while (r < 1)
	{
		depth = 0;
		float dist_v = 1000000;
		float vertical_x = data->player.x;
		float vertical_y = data->player.y;
		float neg_tan = -tan(ray_angle);

		if (ray_angle > PI2 && ray_angle < PI3)
		{
			ray_x = (((int)data->player.x >> 6) << 6) -0.0001;
			ray_y = (data->player.x - ray_x) * neg_tan + data->player.y;
			step_x = -64;
			step_y = -step_x * neg_tan;
		}
		if (ray_angle < PI2 || ray_angle > PI3)
		{
			ray_x = (((int)data->player.x >> 6) << 6) + 64;
			ray_y = (data->player.x - ray_x) * neg_tan + data->player.y;
			step_x = 64;
			step_y = -step_x * neg_tan;
		}
		if (ray_angle == 0 || ray_angle == PI)
		{
			ray_x = data->player.x;
			ray_y = data->player.y;
			depth = 8;
		}
		while (depth < 8)
		{
			map_x = (int)ray_x >> 6;
			map_y = (int)ray_y >> 6;
			map_pos = map_y * data->map.width + map_x;
			if (map_pos > 0 && map_pos < data->map.width * data->map.height && data->map.tiles[map_pos] == 1)
			{
				vertical_x = ray_x;
				vertical_y = ray_y;
				dist_v = dist(data->player.x, data->player.y, vertical_x, vertical_y, ray_angle);
				depth = 8;
			}
			else
			{
				ray_x += step_x;
				ray_y += step_y;
				depth += 1;
			}
		}
		r++;
	}
		

    // Draw the ray from player to the wall
    draw_line_on_image(addr, data->w.width, data->w.height, 
                        data->player.x + data->player.size / 2, 
                        data->player.y + data->player.size / 2, 
                        ray_x, ray_y, 0x0000FF); // Example: Drawing the ray in red
}
*/

float calculate_distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));

}

int max(int a, int b)
{
    if (a > b)
		return a;
	else 
		return b;
}



void calculate_horizontal_distance(t_main_data *data, float *dist, float *ray_x, float *ray_y)
{
    int map_x, map_y, map_pos, depth;
    float ray_angle, step_x, step_y;

    ray_angle = data->player.angle;
	
	int r = 0;
	while (r < 1)
	{
		depth = 0;
		float inverse_tan = -1/(tan(ray_angle));
		if (ray_angle > PI)
		{
			*ray_y = (((int)data->player.y >> 6) << 6) -0.0001;
			*ray_x = (data->player.y - *ray_y) * inverse_tan + data->player.x;
			step_y = -64;
			step_x = -step_y * inverse_tan;
		}
		if (ray_angle < PI)
		{
			*ray_y = (((int)data->player.y >> 6) << 6) + 64;
			*ray_x = (data->player.y - *ray_y) * inverse_tan + data->player.x;
			step_y = 64;
			step_x = -step_y * inverse_tan;
		}
		if (ray_angle == 0 || ray_angle == PI)
		{
			*ray_x = data->player.x;
			*ray_y = data->player.y;
			depth = 8;
		}
		while (depth < 8)
		{
			map_x = (int)(*ray_x) >> 6;
			map_y = (int)(*ray_y) >> 6;
			map_pos = map_y * data->map.width + map_x;
			if (map_pos > 0 && map_pos < data->map.width * data->map.height && data->map.tiles[map_pos] == 1)
			{
				*dist = calculate_distance(data->player.x + data->player.size / 2, data->player.y + data->player.size / 2, *ray_x, *ray_y);
                break; // Exit loop once wall is hit
			}
			else
			{
				*ray_x += step_x;
				*ray_y += step_y;
				depth += 1;
			}
		}
		r++;
	}
}

void calculate_vertical_distance(t_main_data *data, float *dist, float *ray_x, float *ray_y)
{
    int map_x, map_y, map_pos, depth;
    float ray_angle, step_x, step_y;

    ray_angle = data->player.angle;

	*dist = calculate_distance(data->player.x + data->player.size / 2, 
                           data->player.y + data->player.size / 2, 
                           *ray_x, *ray_y);
	
	int r = 0;
	while (r < 1)
	{
		depth = 0;
		float neg_tan = -tan(ray_angle);

		if (ray_angle > PI2 && ray_angle < PI3)
		{
			*ray_x = (((int)data->player.x >> 6) << 6) -0.0001;
			*ray_y = (data->player.x - *ray_x) * neg_tan + data->player.y;
			step_x = -64;
			step_y = -step_x * neg_tan;
		}
		if (ray_angle < PI2 || ray_angle > PI3)
		{
			*ray_x = (((int)data->player.x >> 6) << 6) + 64;
			*ray_y = (data->player.x - *ray_x) * neg_tan + data->player.y;
			step_x = 64;
			step_y = -step_x * neg_tan;
		}
		if (ray_angle == 0 || ray_angle == PI)
		{
			*ray_x = data->player.x;
			*ray_y = data->player.y;
			depth = 8;
		}
		while (depth < 8)
		{
			map_x = (int)(*ray_x) >> 6;
			map_y = (int)(*ray_y) >> 6;
			map_pos = map_y * data->map.width + map_x;
			if (map_pos > 0 && map_pos < data->map.width * data->map.height && data->map.tiles[map_pos] == 1)
			{
				*dist = calculate_distance(data->player.x + data->player.size / 2, data->player.y + data->player.size / 2, *ray_x, *ray_y);
                break; // Exit loop once wall is hit
			}
			else
			{
				*ray_x += step_x;
				*ray_y += step_y;
				depth += 1;
			}
		}
		r++;
	}
}

void draw_shortest_ray(t_main_data *data, int *addr)
{
    float dist_h = 1000000, dist_v = 1000000;
    float horizontal_x = 0, horizontal_y = 0, vertical_x = 0, vertical_y = 0;

    calculate_horizontal_distance(data, &dist_h, &horizontal_x, &horizontal_y);
    calculate_vertical_distance(data, &dist_v, &vertical_x, &vertical_y);

    // Compare distances and draw the shortest ray
    if (dist_h < dist_v) {
        // Draw horizontal ray if it's shorter
        draw_line_on_image(addr, data->w.width, data->w.height, 
            data->player.x + data->player.size / 2, 
            data->player.y + data->player.size / 2, 
            horizontal_x, horizontal_y, 0xFF0000); // Red for horizontal
    } else {
        // Draw vertical ray if it's shorter or equal
        draw_line_on_image(addr, data->w.width, data->w.height, 
            data->player.x + data->player.size / 2, 
            data->player.y + data->player.size / 2, 
            vertical_x, vertical_y, 0x0000FF); // Blue for vertical
    }
}


/*
void draw_horizontal_rays(t_main_data *data, int *addr)
{
    int map_x, map_y, map_pos, depth;
    float ray_x, ray_y, ray_angle, step_x, step_y;

    ray_angle = data->player.angle;
	
	int r = 0;
	while (r < 1)
	{
		depth = 0;
		float dist_h = 1000000;
		float horizontal_x = data->player.x;
		float horizontal_y = data->player.y;
		float inverse_tan = -1/(tan(ray_angle));
		if (ray_angle > PI)
		{
			ray_y = (((int)data->player.y >> 6) << 6) -0.0001;
			ray_x = (data->player.y - ray_y) * inverse_tan + data->player.x;
			step_y = -64;
			step_x = -step_y * inverse_tan;
		}
		if (ray_angle < PI)
		{
			ray_y = (((int)data->player.y >> 6) << 6) + 64;
			ray_x = (data->player.y - ray_y) * inverse_tan + data->player.x;
			step_y = 64;
			step_x = -step_y * inverse_tan;
		}
		if (ray_angle == 0 || ray_angle == PI)
		{
			ray_x = data->player.x;
			ray_y = data->player.y;
			depth = 8;
		}
		while (depth < 8)
		{
			map_x = (int)ray_x >> 6;
			map_y = (int)ray_y >> 6;
			map_pos = map_y * data->map.width + map_x;
			if (map_pos > 0 && map_pos < data->map.width * data->map.height && data->map.tiles[map_pos] == 1)
			{
				horizontal_x = ray_x;
				horizontal_y = ray_y;
				dist_h = dist(data->player.x, data->player.y, horizontal_x, horizontal_y, ray_angle);
				depth = 8;
			}
			else
			{
				ray_x += step_x;
				ray_y += step_y;
				depth += 1;
			}
		}
		r++;
	}
		

    // Draw the ray from player to the wall
    draw_line_on_image(addr, data->w.width, data->w.height, 
                        data->player.x + data->player.size / 2, 
                        data->player.y + data->player.size / 2, 
                        ray_x, ray_y, 0xFF0000); // Example: Drawing the ray in red
}
*/



void draw_player_direction(t_main_data *data, int *addr)
{
    int line_length = 20;

	int start_x = data->player.x + data->player.size / 2;
    int start_y = data->player.y + data->player.size / 2;

    int line_end_x = start_x + cos(data->player.angle) * line_length;
    int line_end_y = start_y + sin(data->player.angle) * line_length;
    
    draw_line_on_image(addr, data->w.width, data->w.height, start_x, start_y, line_end_x, line_end_y, 0xFFFF00);
}

/*
int *addr = (int *)mlx_get_data_addr(
    void *image,                 // The image object whose pixel data address you're retrieving
    int *bits_per_pixel,         // Pointer to an integer to store the number of bits used for each pixel in the image
    int *size_of_line,           // Pointer to an integer to store the number of bytes used to store one line of the image
    int *endian                  // Pointer to an integer to store the endianess of the pixel data
);
*/

int draw(t_main_data *data)
{
	void *frame = mlx_new_image(data->w.mlx, data->w.width, data->w.height);
    int *addr = (int *)mlx_get_data_addr(frame, &(int){32}, &(int){data->w.width * 4}, &(int){0});
	draw_map(data, addr);
	draw_grid_lines(data, addr);
    draw_player(data, addr);
	draw_player_direction(data, addr);
	//draw_horizontal_rays(data, addr);
	//draw_vertical_rays(data, addr);
	draw_shortest_ray(data, addr);
	mlx_put_image_to_window(data->w.mlx, data->w.mlx_win, frame, 0, 0);
	mlx_destroy_image(data->w.mlx, frame);
	return 0;
}

void create_window(t_main_data *data)
{
	data->w.height = 512;
	data->w.width = 1024;
	data->w.mlx = mlx_init();
	data->w.mlx_win = mlx_new_window(data->w.mlx, data->w.width, data->w.height, "Cub3d");
}

void init_player(t_main_data *data)
{
	data->player.x = 200;
    data->player.y = 400;
    data->player.size = 10;
	data->player.color = 0xFFFF00;
	data->player.angle = 0;
	data->player.angle += 0.0001;
	data->player.dx = cos(data->player.angle) * 5;
	data->player.dy = sin(data->player.angle) * 5; 
}

void init_map(t_main_data *data)
{
    int map_tiles[MAX_TILES] =
	{
        1,1,1,1,1,1,1,1,
        1,0,1,0,0,0,0,1,
        1,0,1,0,0,0,0,1,
        1,0,1,0,0,0,0,1,
        1,0,0,0,0,1,0,1,
        1,0,0,0,0,1,0,1,
        1,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1
    };

	int i = 0;
    while (i < MAX_TILES)
	{
        data->map.tiles[i] = map_tiles[i];
		i++;
    }

    data->map.width = 8;
    data->map.height = 8;
    data->map.size = 64;
}

void init(t_main_data *data)
{
	create_window(data);

	// Player initialization
	init_player(data);	

	// Map initialization
	init_map(data);

	mlx_hook(data->w.mlx_win, 2, 1L<<0, keys, data);
 	mlx_loop_hook(data->w.mlx, draw, data);
	mlx_loop(data->w.mlx);
}