#include "cub3d.h"

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
	data->color_buffer = (u_int32_t *)malloc(sizeof(u_int32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
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