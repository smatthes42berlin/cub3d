#include "cub3d.h"

void draw_tile(int *addr, int tile_x, int tile_y, int tile_color, t_main_data *data)
{
	int scaled_tile_size = (int)(TILE_SIZE * MINIMAP_SCALE_FACTOR);

    int y = 0; 
	int x;
	int pixel_index;
    while (y < scaled_tile_size)
	{
		x = 0;
        while (x < scaled_tile_size)
		{
            pixel_index = ((tile_y + y) * data->w.width + (tile_x + x));
            if (pixel_index < data->w.width * data->w.height)
			{
                addr[pixel_index] = tile_color;
            }
			x++;
        }
		y++;
    }
}

void draw_map(t_main_data *data, int *addr)
{
    int i = 0;
	int j;
    while (i < MAP_NUM_ROWS)
	{
		j = 0;
        while (j < MAP_NUM_COLS)
		{
            int tile_x = j * TILE_SIZE ;
            int tile_y = i * TILE_SIZE;
            int tile_color = map[i][j] != 0 ? 0xFFFFFF : 0x000000;
            draw_tile(addr,
					tile_x * MINIMAP_SCALE_FACTOR,
					tile_y * MINIMAP_SCALE_FACTOR,
					tile_color, data);
			j++;
        }
		i++;
    }
}

void draw_rays(t_main_data *data, int *addr, t_ray *rays)
{
	int i = 0;
	while (i < NUM_RAYS)
	{
		draw_line_on_image(addr, data->w.width, data->w.height, 
                        data->player.x * MINIMAP_SCALE_FACTOR, 
                        data->player.y * MINIMAP_SCALE_FACTOR, 
                        rays[i].wall_hit_x * MINIMAP_SCALE_FACTOR, rays[i].wall_hit_y * MINIMAP_SCALE_FACTOR, 0xFF0000); 
		i++;
	}

}