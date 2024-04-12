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


int keys(int key, void *param)
{
    t_main_data *data = (t_main_data *)param;

    if (key == 65307)
    {
        destroy_window(data);
        exit(0);
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
	data->player.size = 10;
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

	
