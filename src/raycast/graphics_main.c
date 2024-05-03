#include "cub3d.h"

int	graphics_main(t_main_data *data)
{
	init_map(data);
	if (!initialize_window(data))
	{
		destroy_window(data);
		return (FALSE);
	}
	init_player(data);
	free_parse_state(data->parse_state);
	create_wall_texture(data);
	mlx_hook(data->w.mlx_win, 2, 1L << 0, keys, data);
	mlx_hook(data->w.mlx_win, 17, 0, close_window, data);
	mlx_loop_hook(data->w.mlx, draw, data);
	mlx_loop(data->w.mlx);
	destroy_window(data);
	return (TRUE);
}
