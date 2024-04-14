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

float normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return angle;
}

float distance_between_points(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


void cast_ray(t_main_data *data, t_ray *rays, float ray_angle, int strip_id)
{
	ray_angle = normalize_angle(ray_angle);

	int is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	int is_ray_facing_up = !is_ray_facing_down;

	int is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	int is_ray_facing_left = !is_ray_facing_right;

	////////////////////////////////////////
	/// HORIZONTAL GRID INTERSECTION CODE
	////////////////////////////////////////

	float xintercept;
	float yintercept;

	float xstep;
	float ystep;

	int found_horz_wall_hit = FALSE;
	float horz_wall_hit_x = 0;
	float horz_wall_hit_y = 0;
	int horz_wall_content = 0;

	yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += is_ray_facing_down ? TILE_SIZE : 0;

	xintercept = data->player.x + (yintercept - data->player.y) / tan(ray_angle);

	ystep = TILE_SIZE;
	ystep *= is_ray_facing_up ? -1 : 1;

	xstep = TILE_SIZE / tan(ray_angle);
	xstep *= (is_ray_facing_left && xstep > 0) ? -1 : 1;
	xstep *= (is_ray_facing_right && xstep < 0) ? -1 : 1;

	float next_horz_touch_x = xintercept;
	float next_horz_touch_y = yintercept;

	while (next_horz_touch_x >= 0 && next_horz_touch_x <= WINDOW_WIDTH && next_horz_touch_y >= 0 && next_horz_touch_y <= WINDOW_HEIGHT)
	{
		float x_to_check = next_horz_touch_x;
		float y_to_check = next_horz_touch_y + (is_ray_facing_up ? -1 : 0);

		if (map_has_wall_at(x_to_check, y_to_check))
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			horz_wall_content = map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			found_horz_wall_hit = TRUE;
			break;
		}
		else
		{
			next_horz_touch_x += xstep;
			next_horz_touch_y += ystep;
		}
	}

	////////////////////////////////////////
	/// VERTICAL GRID INTERSECTION CODE
	////////////////////////////////////////

	int found_vert_wall_hit = FALSE;
	float vert_wall_hit_x = 0;
	float vert_wall_hit_y = 0;
	int vert_wall_content = 0;

	xintercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += is_ray_facing_right ? TILE_SIZE : 0;

	yintercept = data->player.y + (xintercept - data->player.x) * tan(ray_angle);

	xstep = TILE_SIZE;
	xstep *= is_ray_facing_left ? -1 : 1;

	ystep = TILE_SIZE * tan(ray_angle);
	ystep *= (is_ray_facing_up && ystep > 0) ? -1 : 1;
	ystep *= (is_ray_facing_down && ystep < 0) ? -1 : 1;

	float next_vert_touch_x = xintercept;
	float next_vert_touch_y = yintercept;

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= WINDOW_WIDTH && next_vert_touch_y >= 0 && next_vert_touch_y <= WINDOW_HEIGHT)
	{
		float x_to_check = next_vert_touch_x + (is_ray_facing_left ? -1 : 0);
		float y_to_check = next_vert_touch_y;

		if (map_has_wall_at(x_to_check, y_to_check))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			vert_wall_content = map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			found_vert_wall_hit = TRUE;
			break;
		}
		else
		{
			next_vert_touch_x += xstep;
			next_vert_touch_y += ystep;
		}
	}

	float horz_hit_distance = found_horz_wall_hit
		? distance_between_points(data->player.x, data->player.y, horz_wall_hit_x, horz_wall_hit_y)
		: (float)INT_MAX;

	float vert_hit_distance = found_vert_wall_hit
		? distance_between_points(data->player.x, data->player.y, vert_wall_hit_x, vert_wall_hit_y)
		: (float)INT_MAX;

	if (vert_hit_distance < horz_hit_distance)
	{
		rays[strip_id].distance = vert_hit_distance;
		rays[strip_id].wall_hit_x = vert_wall_hit_x;
		rays[strip_id].wall_hit_y = vert_wall_hit_y;
		rays[strip_id].wall_hit_content = vert_wall_content;	
		rays[strip_id].was_hit_vertical = TRUE;
	}
	else
	{
		rays[strip_id].distance = horz_hit_distance;
		rays[strip_id].wall_hit_x = horz_wall_hit_x;
		rays[strip_id].wall_hit_y = horz_wall_hit_y;
		rays[strip_id].wall_hit_content = horz_wall_content;	
		rays[strip_id].was_hit_vertical = FALSE;
	}
	rays[strip_id].ray_angle = ray_angle;
	rays[strip_id].is_ray_facing_down = is_ray_facing_down;
	rays[strip_id].is_ray_facing_up = is_ray_facing_up;
	rays[strip_id].is_ray_facing_left = is_ray_facing_left;
	rays[strip_id].is_ray_facing_right = is_ray_facing_right;
}

void cast_all_rays(t_main_data *data, t_ray *rays)
{
	float ray_angle = data->player.rotation_angle - (FOV_ANGLE / 2);

	int strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		cast_ray(data, rays, ray_angle, strip_id);
		strip_id++;
		ray_angle += FOV_ANGLE / NUM_RAYS;
	}
}

void draw_rays(t_main_data *data, int *addr, t_ray *rays)
{
	int i = 0;
	while (i < NUM_RAYS)
	{
		draw_line_on_image(addr, data->w.width, data->w.height, 
                        data->player.x * MINIMAP_SCALE_FACTOR, 
                        data->player.y * MINIMAP_SCALE_FACTOR, 
                        rays[i].wall_hit_x * MINIMAP_SCALE_FACTOR, rays[i].wall_hit_y * MINIMAP_SCALE_FACTOR, 0xFF0000); 
		i++;
	}

}

int draw(t_main_data *data)
{
	void *frame = mlx_new_image(data->w.mlx, data->w.width, data->w.height);
	
    int *addr = (int *)mlx_get_data_addr(frame, &(int){32}, &(int){data->w.width * 4}, &(int){0});
	static t_ray rays[NUM_RAYS];
	cast_all_rays(data, rays);
	render(data, addr, rays);

	mlx_put_image_to_window(data->w.mlx, data->w.mlx_win, frame, 0, 0);
	mlx_destroy_image(data->w.mlx, frame);
	return 0;
}

void render(t_main_data *data, int *addr, t_ray *rays)
{
	draw_map(data, addr);
	draw_player(data, addr);
	draw_player_direction(data, addr);
	draw_rays(data, addr, rays);

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

	
