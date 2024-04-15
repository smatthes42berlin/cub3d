#include "cub3d.h"

void	destroy_window(t_main_data *data)
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
	if (data->color_buffer)
		free(data->color_buffer);
}

int	close_window(void *param)
{
	t_main_data *data = (t_main_data *)param;

	destroy_window(data);
	exit(0);
	return (0);
}