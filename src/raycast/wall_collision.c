#include "cub3d.h"

bool	check_collision(t_main_data *data, float new_x, float new_y)
{
	int		angle;
	float	buffer;
	float	rad;
	float	check_x;
	float	check_y;

	angle = 0;
	buffer = 3;
	while (angle < 360)
	{
		rad = angle * (PI / 180);
		check_x = new_x + cos(rad) * buffer;
		check_y = new_y + sin(rad) * buffer;
		if (map_has_wall_at(data, check_x, check_y))
			return (true);
		angle += 30;
	}
	return (false);
}

int	map_has_wall_at(t_main_data *data, float x, float y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	if (x < 0 || x >= data->w.width || y < 0 || y >= data->w.height)
		return (TRUE);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	return (data->map.map[map_grid_index_y][map_grid_index_x] == '1');
}
