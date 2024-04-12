#include "cub3d.h"

int map[MAP_NUM_ROWS][MAP_NUM_COLS] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

void destroy_window(t_main_data *data)
{
	t_xvar	*xvar;

	if (data->w.mlx_win != NULL)
    {
        mlx_destroy_window(data->w.mlx, data->w.mlx_win);
        data->w.mlx_win = NULL;
    }
    if (data->w.mlx != NULL)
    {
        xvar = (t_xvar *)data->w.mlx;
		if (xvar && xvar->display)
		{
			XCloseDisplay(xvar->display);
		}
		free(data->w.mlx);
        data->w.mlx = NULL;
    }
}

int close_window(void *param)
{
    t_main_data *data = (t_main_data *)param;

    destroy_window(data);
    exit(0);
    return 0;
}

int map_has_wall_at(float x, float y)
{
	if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE)
		return TRUE;

	int map_grid_index_x = floor(x / TILE_SIZE);
	int map_grid_index_y = floor(y / TILE_SIZE);
	return map[map_grid_index_y][map_grid_index_x] != 0;

}

int keys(int key, void *param)
{
    t_main_data *data = (t_main_data *)param;

	float new_player_x = data->player.x;
    float new_player_y = data->player.y;
    if (key == 65307)
    {
        destroy_window(data);
        exit(0);
    }
	if (key == 'a') // Strafe left
	{
		new_player_x += sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
		new_player_y -= cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}
	if (key == 'd') // Strafe right
	{
		new_player_x -= sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
		new_player_y += cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}
	if (key == 'w') // Move forward
	{
    	new_player_x += cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
    	new_player_y += sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}
	if (key == 's') // Move backward
	{
    	new_player_x -= cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
    	new_player_y -= sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}

	if (key == 65361) // Left
	{
    	data->player.rotation_angle -= ROTATION_MOVEMENT;
    	if (data->player.rotation_angle < 0)
			data->player.rotation_angle += TWO_PI;
    	//data->player.delta_x = cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
    	//data->player.delta_y = sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}
	if (key == 65363) // Right
	{
    	data->player.rotation_angle += ROTATION_MOVEMENT;
    	if (data->player.rotation_angle >= TWO_PI)
			data->player.rotation_angle -= TWO_PI;
    	//data->player.delta_x = cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
    	//data->player.delta_y = sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}

	if (!map_has_wall_at(new_player_x, new_player_y))
	{
		data->player.x = new_player_x;
		data->player.y = new_player_y;
	}
    return 0;
}

void update(t_main_data *data)
{

	data->player.x += 1;
	//data->player.y += 1;

}

void draw_tile(int *addr, int tile_x, int tile_y, int tile_color, t_main_data *data)
{
    int y = 0; 
	int x;
	int pixel_index;
    while (y < TILE_SIZE)
	{
		x = 0;
        while (x < TILE_SIZE)
		{
            pixel_index = ((tile_y + y) * data->w.width + (tile_x + x));
            if (pixel_index < data->w.width * data->w.height)
			{
                addr[pixel_index] = tile_color;
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

void draw_player_direction(t_main_data *data, int *addr)
{
    int scaled_line_length = 30 * MINIMAP_SCALE_FACTOR; // Apply scaling to line length as well

    // Calculate the middle point of the player, applying the scale factor uniformly
    int start_x = (data->player.x + data->player.size / 2) * MINIMAP_SCALE_FACTOR;
    int start_y = (data->player.y + data->player.size / 2) * MINIMAP_SCALE_FACTOR;

    // Calculate the end point of the line, applying the scale factor to the line length
    int line_end_x = start_x + cos(data->player.rotation_angle) * scaled_line_length;
    int line_end_y = start_y + sin(data->player.rotation_angle) * scaled_line_length;
    
    draw_line_on_image(addr, data->w.width, data->w.height, start_x, start_y, line_end_x, line_end_y, 0xFFFF00);
}


void draw_map(t_main_data *data, int *addr)
{
    int i = 0;
	int j;
    while (i < MAP_NUM_ROWS)
	{
		j = 0;
        while (j < MAP_NUM_COLS)
		{
            int tile_x = j * TILE_SIZE ;
            int tile_y = i * TILE_SIZE;
            int tile_color = map[i][j] != 0 ? 0xFFFFFF : 0x000000;
            draw_tile(addr,
					tile_x * MINIMAP_SCALE_FACTOR,
					tile_y * MINIMAP_SCALE_FACTOR,
					tile_color, data);
			j++;
        }
		i++;
    }
}


void draw_player(t_main_data *data, int *addr)
{
    int y = 0;
    int scaled_size = data->player.size * MINIMAP_SCALE_FACTOR; // Scale the size of the player
    while (y < scaled_size) // Use scaled size
    {
        int x = 0;
        while (x < scaled_size) // Use scaled size
        {
            // Calculate the scaled position of the player
            int scaled_x = data->player.x * MINIMAP_SCALE_FACTOR + x;
            int scaled_y = data->player.y * MINIMAP_SCALE_FACTOR + y;

            // Ensure we are within the window boundaries
            if (scaled_x >= 0 && scaled_x < data->w.width && scaled_y >= 0 && scaled_y < data->w.height)
            {
                int pixel_index = scaled_y * data->w.width + scaled_x;
                addr[pixel_index] = data->player.color;
            }
            x++;
        }
        y++;
    }
}


void render(t_main_data *data, int *addr)
{
	draw_map(data, addr);
	draw_player(data, addr);
	draw_player_direction(data, addr);

}


int draw(t_main_data *data)
{
	void *frame = mlx_new_image(data->w.mlx, data->w.width, data->w.height);
	
    int *addr = (int *)mlx_get_data_addr(frame, &(int){32}, &(int){data->w.width * 4}, &(int){0});
	//update(data);
	render(data, addr);
	mlx_put_image_to_window(data->w.mlx, data->w.mlx_win, frame, 0, 0);
	mlx_destroy_image(data->w.mlx, frame);
	return 0;
}

int initialize_window(t_main_data *data)
{
	data->w.height = WINDOW_HEIGHT;
	data->w.width = WINDOW_WIDTH;
	data->w.mlx = mlx_init();
	if (data->w.mlx == NULL)
		return FALSE;
	data->w.mlx_win = mlx_new_window(data->w.mlx, data->w.width, data->w.height, "Cub3d");
	if (data->w.mlx_win == NULL)
		return FALSE;
	return TRUE;
}

void init_player(t_main_data *data)
{
	data->player.x = WINDOW_WIDTH / 2;
    data->player.y = WINDOW_HEIGHT / 2;
	data->player.size = 1;
	data->player.color = 0xFFFF00;
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
	data->player.rotation_angle = PI / 2;
	data->player.walk_speed = 100;
	data->player.turn_speed = 45 * (PI / 180);
}


void setup(t_main_data *data)
{
	init_player(data);
}

int init(t_main_data *data)
{
    if (!initialize_window(data))
	{
        destroy_window(data);
        return FALSE;
    }

	setup(data);

	mlx_hook(data->w.mlx_win, 2, 1L<<0, keys, data);
	mlx_hook(data->w.mlx_win, 17, 0, close_window, data);
    mlx_loop_hook(data->w.mlx, draw, data);
	mlx_loop(data->w.mlx);

    destroy_window(data);
    return TRUE;
}

	
