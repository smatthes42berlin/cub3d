#include "cub3d.h"

void	fill_rect(int *addr, t_minimap *minimap)
{
	int	pixel_index;
	int	j;
	int	i;

	j = minimap->offset_y;
	while (j < minimap->offset_y + minimap->height)
	{
		i = minimap->offset_x;
		while (i < minimap->offset_x + minimap->width)
		{
			pixel_index = j * WINDOW_WIDTH + i;
			if (pixel_index < WINDOW_WIDTH * WINDOW_HEIGHT)
				addr[pixel_index] = minimap->color;
			i++;
		}
		j++;
	}
}

void	init_minimap(t_main_data *data, t_minimap *minimap)
{
	minimap->offset_x = 0;
	minimap->offset_y = 0;
	minimap->width = data->minimap_width;
	minimap->height = data->minimap_height;
	minimap->color = 0xFF000000;
}

void	calculate_minimap_dimensions(t_main_data *data)
{
	int	minimap_width;
	int	minimap_height;

	minimap_width = (int)(data->map.cols * TILE_SIZE * data->scale_factor);
	minimap_height = (int)(data->map.rows * TILE_SIZE * data->scale_factor);
	data->minimap_width = minimap_width;
	data->minimap_height = minimap_height;
}

void	render(t_main_data *data, int *addr, t_ray *rays)
{
	t_minimap	minimap;

	fill_color_buffer(data, 0xFF000000);
	generate_3d_projection(data, rays);
	ft_memcpy(addr, data->color_buffer, WINDOW_WIDTH * WINDOW_HEIGHT
		* sizeof(u_int32_t));
	if (data->map.rows <= 50 && data->map.cols <= 50)
	{
		if (data->map.rows > 24 || data->map.cols > 24)
		{
			data->scale_factor = 0.11;
			data->movement = 25;
		}
		calculate_minimap_dimensions(data);
		init_minimap(data, &minimap);
		fill_rect(addr, &minimap);
		draw_map(data, addr);
		draw_player(data, addr);
		draw_player_direction(data, addr);
		draw_rays(data, addr, rays);
	}
}

int	draw(t_main_data *data)
{
	void			*frame;
	int				*addr;
	static t_ray	rays[NUM_RAYS];

	frame = mlx_new_image(data->w.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	addr = (int *)mlx_get_data_addr(frame, &(int){32}, &(int){WINDOW_WIDTH * 4},
			&(int){0});
	cast_all_rays(data, rays);
	render(data, addr, rays);
	mlx_put_image_to_window(data->w.mlx, data->w.mlx_win, frame, 0, 0);
	mlx_destroy_image(data->w.mlx, frame);
	return (0);
}
