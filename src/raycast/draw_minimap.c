#include "cub3d.h"

void	draw_tile(int *addr, int tile_x, int tile_y, int tile_color)
{
	int	scaled_tile_size;
	int	y;
	int	x;
	int	pixel_index;

	scaled_tile_size = (int)(TILE_SIZE * MINIMAP_SCALE_FACTOR);
	y = 0;
	while (y < scaled_tile_size)
	{
		x = 0;
		while (x < scaled_tile_size)
		{
			pixel_index = ((tile_y + y) * WINDOW_WIDTH + (tile_x + x));
			if (pixel_index < WINDOW_WIDTH * WINDOW_HEIGHT)
			{
				addr[pixel_index] = tile_color;
			}
			x++;
		}
		y++;
	}
}

void	draw_map(t_main_data *data, int *addr)
{
	int	i;
	int	j;
	int	tile_x;
	int	tile_y;
	int	tile_color;

	i = 0;
	while (i < data->map.rows)
	{
		j = 0;
		while (j < data->map.cols)
		{
			tile_x = j * TILE_SIZE;
			tile_y = i * TILE_SIZE;
			if (data->map.map[i][j] == '1')
				tile_color = 0xFFFFFF;
			else
				tile_color = 0x000000;
			draw_tile(addr, tile_x * MINIMAP_SCALE_FACTOR, tile_y
				* MINIMAP_SCALE_FACTOR, tile_color);
			j++;
		}
		i++;
	}
}

void	draw_rays(t_main_data *data, int *addr, t_ray *rays)
{
	int		i;
	t_line	line;

	line.width = WINDOW_WIDTH;
	line.height = WINDOW_HEIGHT;
	line.start_x = data->player.x * MINIMAP_SCALE_FACTOR;
	line.start_y = data->player.y * MINIMAP_SCALE_FACTOR;
	line.color = 0xFF0000;
	i = 0;
	while (i < NUM_RAYS)
	{
		line.end_x = rays[i].wall_hit_x * MINIMAP_SCALE_FACTOR;
		line.end_y = rays[i].wall_hit_y * MINIMAP_SCALE_FACTOR;
		draw_line_on_image(addr, &line);
		i++;
	}
}
