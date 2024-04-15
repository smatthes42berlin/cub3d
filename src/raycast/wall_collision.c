#include "cub3d.h"

int map_has_wall_at(float x, float y)
{
	if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE)
		return TRUE;

	int map_grid_index_x = floor(x / TILE_SIZE);
	int map_grid_index_y = floor(y / TILE_SIZE);
	return map[map_grid_index_y][map_grid_index_x] != 0;

}