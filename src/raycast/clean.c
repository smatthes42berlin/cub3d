#include "cub3d.h"

void	cleanup_resources(t_main_data *data)
{
	t_xvar	*xvar;

	if (data->w.mlx)
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
	{
		free(data->color_buffer);
		data->color_buffer = NULL;
	}
	free_str_arr_null(data->map.map);
	free(data->textures.north.path);
	free(data->textures.south.path);
	free(data->textures.east.path);
	free(data->textures.west.path);
}

void	destroy_window(t_main_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->textures.all[i] && data->textures.all[i]->img_ptr)
		{
			if (data->w.mlx)
				mlx_destroy_image(data->w.mlx, data->textures.all[i]->img_ptr);
			data->textures.all[i]->img_ptr = NULL;
		}
		i++;
	}
	if (data->w.mlx_win != NULL)
	{
		if (data->w.mlx)
			mlx_destroy_window(data->w.mlx, data->w.mlx_win);
		data->w.mlx_win = NULL;
	}
	cleanup_resources(data);
}

int	close_window(void *param)
{
	t_main_data	*data;

	data = (t_main_data *)param;
	destroy_window(data);
	exit(0);
	return (0);
}
