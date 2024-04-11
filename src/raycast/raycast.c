#include "cub3d.h"

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

int draw(t_main_data *data)
{
	void *frame = mlx_new_image(data->w.mlx, data->w.width, data->w.height);
    //int *addr = (int *)mlx_get_data_addr(frame, &(int){32}, &(int){data->w.width * 4}, &(int){0});
	//draw_map(data, addr);
	//draw_grid_lines(data, addr);
    //draw_player(data, addr);
	//draw_player_direction(data, addr);
	//draw_horizontal_rays(data, addr);
	//draw_vertical_rays(data, addr);
	//draw_rays1(data, addr);
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

int init(t_main_data *data)
{
	//setup();

    if (!initialize_window(data))
	{
        destroy_window(data);
        return FALSE;
    }

	mlx_hook(data->w.mlx_win, 2, 1L<<0, keys, data);
	mlx_hook(data->w.mlx_win, 17, 0, close_window, data);
    mlx_loop_hook(data->w.mlx, draw, data);
	mlx_loop(data->w.mlx);

    destroy_window(data);
    return TRUE;
}

	
