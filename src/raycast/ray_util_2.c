#include "cub3d.h"

int	update_ray_hit_data_hor(t_main_data *data, t_raycast *r, int map_grid_x,
		int map_grid_y)
{
	r->horz_wall_hit_x = r->next_horz_touch_x;
	r->horz_wall_hit_y = r->next_horz_touch_y;
	r->horz_wall_content = data->map.map[map_grid_y][map_grid_x];
	r->found_horz_wall_hit = TRUE;
	return (0);
}

int	update_ray_hit_data_ver(t_main_data *data, t_raycast *r, int map_grid_x,
		int map_grid_y)
{
	r->vert_wall_hit_x = r->next_vert_touch_x;
	r->vert_wall_hit_y = r->next_vert_touch_y;
	r->vert_wall_content = data->map.map[map_grid_y][map_grid_x];
	r->found_vert_wall_hit = TRUE;
	return (0);
}

// warum macht man -1?
int	get_next_pt_to_check_ver(float *x, float *y, t_raycast *r)
{
	*y = r->next_vert_touch_y;
	*x = r->next_vert_touch_x;
	if (r->is_ray_facing_left)
		*x -= 1;
	return (0);
}

// warum macht man -1?
int	get_next_pt_to_check_hor(float *x, float *y, t_raycast *r)
{
	*x = r->next_horz_touch_x;
	*y = r->next_horz_touch_y;
	if (r->is_ray_facing_up)
		*y -= 1;
	return (0);
}

int	calculate_distance_hor(t_main_data *data, t_raycast r, float *dist)
{
	*dist = FLT_MAX;
	if (r.found_horz_wall_hit)
		*dist = distance_between_points(data->player.x,
				data->player.y, r.horz_wall_hit_x, r.horz_wall_hit_y);
	return (0);
}
