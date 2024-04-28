#include "cub3d.h"

int	calculate_distance_ver(t_main_data *data, t_raycast r, float *dist)
{
	*dist = FLT_MAX;
	if (r.found_vert_wall_hit)
		*dist = distance_between_points(data->player.x,
				data->player.y, r.vert_wall_hit_x, r.vert_wall_hit_y);
	return (0);
}

int	update_ray_with_closest_hit(t_raycast *r, t_ray *ray, float vert_dist,
		float hor_dist)
{
	if (vert_dist < hor_dist)
		update_ray_with_vertical_hit(ray, r, vert_dist);
	else
		update_ray_with_horizontal_hit(ray, r, hor_dist);
	return (0);
}
