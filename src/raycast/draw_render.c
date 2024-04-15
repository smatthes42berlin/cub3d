#include "cub3d.h"

void render(t_main_data *data, int *addr, t_ray *rays)
{
	fill_color_buffer(0xFF000000, data->color_buffer);
	generate_3d_projection(data, rays);

	memcpy(addr, data->color_buffer, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(u_int32_t));

	// display mini-map
	draw_map(data, addr);
	draw_player(data, addr);
	draw_player_direction(data, addr);
	draw_rays(data, addr, rays);

}


int draw(t_main_data *data)
{
	void *frame = mlx_new_image(data->w.mlx, data->w.width, data->w.height);
	
    int *addr = (int *)mlx_get_data_addr(frame, &(int){32}, &(int){data->w.width * 4}, &(int){0});
	static t_ray rays[NUM_RAYS];
	cast_all_rays(data, rays);
	render(data, addr, rays);

	mlx_put_image_to_window(data->w.mlx, data->w.mlx_win, frame, 0, 0);
	mlx_destroy_image(data->w.mlx, frame);
	return 0;
}