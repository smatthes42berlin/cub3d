#include "cub3d.h"

void	init_raycast(t_raycast *r, float ray_angle)
{
	r->ray_angle = normalize_angle(ray_angle);
	r->is_ray_facing_down = r->ray_angle > 0 && r->ray_angle < PI;
	r->is_ray_facing_up = !r->is_ray_facing_down;
	r->is_ray_facing_right = r->ray_angle < 0.5 * PI || r->ray_angle > 1.5 * PI;
	r->is_ray_facing_left = !r->is_ray_facing_right;
}

void	cast_ray(t_main_data *data, t_ray *ray, float ray_angle)
{
	t_raycast	r;
	float		horz_hit_distance;
	float		vert_hit_distance;

	init_raycast(&r, ray_angle);
	cast_horizontal_ray(data, &r);
	cast_vertical_ray(data, &r);
	calculate_distance_hor(data, r, &horz_hit_distance);
	calculate_distance_ver(data, r, &vert_hit_distance);
	update_ray_with_closest_hit(&r, ray, vert_hit_distance, horz_hit_distance);
}

void	cast_all_rays(t_main_data *data, t_ray *rays)
{
	float	ray_angle;
	int		strip_id;

	ray_angle = data->player.rotation_angle - (data->fov_angle / 2);
	strip_id = 0;
	while (strip_id < data->num_rays)
	{
		cast_ray(data, &(rays[strip_id]), ray_angle);
		strip_id++;
		ray_angle += data->fov_angle / data->num_rays;
	}
}
