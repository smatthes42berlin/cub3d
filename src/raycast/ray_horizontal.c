#include "cub3d.h"

void	init_horizontal_ray(t_main_data *data, t_raycast *r)
{
	r->found_horz_wall_hit = FALSE;
	r->horz_wall_hit_x = 0;
	r->horz_wall_hit_y = 0;
	r->horz_wall_content = 0;
	r->yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	if (r->is_ray_facing_down)
		r->yintercept += TILE_SIZE;
	r->xintercept = data->player.x + (r->yintercept - data->player.y)
		/ tan(r->ray_angle);
	r->ystep = TILE_SIZE;
	if (r->is_ray_facing_up)
		r->ystep *= -1;
	r->xstep = TILE_SIZE / tan(r->ray_angle);
	if (r->is_ray_facing_left && r->xstep > 0)
		r->xstep *= -1;
	if (r->is_ray_facing_right && r->xstep < 0)
		r->xstep *= -1;
	r->next_horz_touch_x = r->xintercept;
	r->next_horz_touch_y = r->yintercept;
	r->main_data = data;
}

void	cast_horizontal_ray(t_main_data *data, t_raycast *r)
{
	float	x_to_check;
	float	y_to_check;
	int		map_grid_index_x;
	int		map_grid_index_y;

	init_horizontal_ray(data, r);
	while (next_grid_pt_within_window(data, r->next_horz_touch_x,
			r->next_horz_touch_y))
	{
		get_next_pt_to_check_hor(&x_to_check, &y_to_check, r);
		get_ray_grid_index(&map_grid_index_x, &map_grid_index_y, x_to_check,
			y_to_check);
		if (grid_index_outside_map(data, map_grid_index_x, map_grid_index_y))
			break ;
		if (wall_hit(data, map_grid_index_x, map_grid_index_y))
		{
			update_ray_hit_data_hor(data, r, map_grid_index_x,
				map_grid_index_y);
			break ;
		}
		else
			step_grid(r, &(r->next_horz_touch_x), &(r->next_horz_touch_y));
	}
}

void	update_ray_with_horizontal_hit(t_ray *ray, t_raycast *r, float distance)
{
	ray->distance = distance;
	ray->wall_hit_x = r->horz_wall_hit_x;
	ray->wall_hit_y = r->horz_wall_hit_y;
	ray->wall_hit_content = r->horz_wall_content;
	ray->was_hit_vertical = FALSE;
	ray->hit_side = &(r->main_data->textures.north);
	if (r->is_ray_facing_down)
		ray->hit_side = &(r->main_data->textures.south);
	ray->ray_angle = r->ray_angle;
	ray->is_ray_facing_down = r->is_ray_facing_down;
	ray->is_ray_facing_up = r->is_ray_facing_up;
	ray->is_ray_facing_left = r->is_ray_facing_left;
	ray->is_ray_facing_right = r->is_ray_facing_right;
}
