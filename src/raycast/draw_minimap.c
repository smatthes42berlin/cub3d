#include "cub3d.h"

void	draw_tile(t_main_data *data, int *addr, t_tile *tile)
{
	int	scaled_tile_size;
	int	y;
	int	x;
	int	pixel_index;

	scaled_tile_size = (int)(TILE_SIZE * data->scale_factor);
	y = 0;
	while (y < scaled_tile_size)
	{
		x = 0;
		while (x < scaled_tile_size)
		{
			pixel_index = ((tile->y + y) * WINDOW_WIDTH + (tile->x + x));
			if (pixel_index < WINDOW_WIDTH * WINDOW_HEIGHT)
				addr[pixel_index] = tile->color;
			x++;
		}
		y++;
	}
}

void	draw_map(t_main_data *data, int *addr)
{
	int		i;
	int		j;
	t_tile	tile;

	i = 0;
	while (i < data->map.rows)
	{
		j = 0;
		while (j < data->map.cols)
		{
			tile.x = j * TILE_SIZE;
			tile.y = i * TILE_SIZE;
			if (data->map.map[i][j] == '1')
				tile.color = 0xFFFFFF;
			else
				tile.color = 0x000000;
			tile.x *= data->scale_factor;
			tile.y *= data->scale_factor;
			draw_tile(data, addr, &tile);
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
	line.start_x = data->player.x * data->scale_factor;
	line.start_y = data->player.y * data->scale_factor;
	line.color = 0xFF0000;
	i = 0;
	while (i < data->num_rays)
	{
		line.end_x = rays[i].wall_hit_x * data->scale_factor;
		line.end_y = rays[i].wall_hit_y * data->scale_factor;
		draw_line_on_image(addr, &line);
		i++;
	}
}
