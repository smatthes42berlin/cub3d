#include "cub3d.h"

bool	next_grid_pt_within_window(t_main_data *data, float touch_x,
		float touch_y)
{
	return (touch_x >= 0 && touch_x <= data->w.width && touch_y >= 0
		&& touch_y <= data->w.height);
}

int	get_ray_grid_index(int *grid_index_x, int *grid_index_y, float x, float y)
{
	*grid_index_x = (int)floor(x / TILE_SIZE);
	*grid_index_y = (int)floor(y / TILE_SIZE);
	return (0);
}

int	grid_index_outside_map(t_main_data *data, int index_x, int index_y)
{
	return (index_x < 0 || index_x >= data->map.cols || index_y < 0
		|| index_y >= data->map.rows);
}

bool	wall_hit(t_main_data *data, int index_x, int index_y)
{
	return (data->map.map[index_y][index_x] == '1');
}

int	step_grid(t_raycast *r, float *x, float *y)
{
	*x += r->xstep;
	*y += r->ystep;
	return (0);
}
