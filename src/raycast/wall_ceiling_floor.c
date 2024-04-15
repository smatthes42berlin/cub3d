#include "cub3d.h"

void	generate_3d_projection(t_main_data *data, t_ray *rays)
{
	int		i;
	float	perp_distance;
	float	distance_proj_plane;
	float	projected_wall_height;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		y;

	i = 0;
	while (i < NUM_RAYS)
	{
		perp_distance = rays[i].distance * cos(rays[i].ray_angle
				- data->player.rotation_angle);
		distance_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		projected_wall_height = (TILE_SIZE / perp_distance)
			* distance_proj_plane;
		wall_strip_height = projected_wall_height;
		wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
		wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
		wall_bottom_pixel = wall_bottom_pixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_bottom_pixel;
		// setting color of ceiling
		y = 0;
		while (y < wall_top_pixel)
		{
			data->color_buffer[(WINDOW_WIDTH * y) + i] = 0xFF333333;
			y++;
		}
		// rendering the walls
		y = wall_top_pixel;
		while (y < wall_bottom_pixel)
		{
			data->color_buffer[(WINDOW_WIDTH * y)
				+ i] = rays[i].was_hit_vertical ? 0xFFFFFFFF : 0xFFCCCCCC;
			y++;
		}
		// setting color of floor
		y = wall_bottom_pixel;
		while (y < WINDOW_HEIGHT)
		{
			data->color_buffer[(WINDOW_WIDTH * y) + i] = 0xFF777777;
			y++;
		}
		i++;
	}
}
