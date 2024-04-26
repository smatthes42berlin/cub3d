#include "cub3d.h"

void	init_vertical_ray(t_main_data *data, t_raycast *r)
{
	r->found_vert_wall_hit = FALSE;
	r->vert_wall_hit_x = 0;
	r->vert_wall_hit_y = 0;
	r->vert_wall_content = 0;
	r->xintercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	if (r->is_ray_facing_right)
		r->xintercept += TILE_SIZE;
	r->yintercept = data->player.y + (r->xintercept - data->player.x)
		* tan(r->ray_angle);
	r->xstep = TILE_SIZE;
	if (r->is_ray_facing_left)
		r->xstep *= -1;
	r->ystep = TILE_SIZE * tan(r->ray_angle);
	if (r->is_ray_facing_up && r->ystep > 0)
		r->ystep *= -1;
	if (r->is_ray_facing_down && r->ystep < 0)
		r->ystep *= -1;
	r->next_vert_touch_x = r->xintercept;
	r->next_vert_touch_y = r->yintercept;
}

void	cast_vertical_ray(t_main_data *data, t_raycast *r)
{
	float	x_to_check;
	float	y_to_check;
	int		map_grid_index_x;
	int		map_grid_index_y;

	init_vertical_ray(data, r);
	while (r->next_vert_touch_x >= 0 && r->next_vert_touch_x <= data->w.width
		&& r->next_vert_touch_y >= 0 && r->next_vert_touch_y <= data->w.height)
	{
		x_to_check = r->next_vert_touch_x + (r->is_ray_facing_left ? -1 : 0);
		y_to_check = r->next_vert_touch_y;
		map_grid_index_x = (int)floor(x_to_check / TILE_SIZE);
		map_grid_index_y = (int)floor(y_to_check / TILE_SIZE);
		if (map_grid_index_x < 0 || map_grid_index_x >= data->map.cols
			|| map_grid_index_y < 0 || map_grid_index_y >= data->map.rows)
		{
			break ;
		}
		if (data->map.map[map_grid_index_y][map_grid_index_x] == '1')
		{
			r->vert_wall_hit_x = r->next_vert_touch_x;
			r->vert_wall_hit_y = r->next_vert_touch_y;
			r->vert_wall_content = data->map.map[map_grid_index_y][map_grid_index_x];
			r->found_vert_wall_hit = TRUE;
			break ;
		}
		else
		{
			r->next_vert_touch_x += r->xstep;
			r->next_vert_touch_y += r->ystep;
		}
	}
}

void	update_ray_with_vertical_hit(t_ray *ray, t_raycast *r, float distance)
{
	ray->distance = distance;
	ray->wall_hit_x = r->vert_wall_hit_x;
	ray->wall_hit_y = r->vert_wall_hit_y;
	ray->wall_hit_content = r->vert_wall_content;
	ray->was_hit_vertical = TRUE;
	ray->hit_side = r->is_ray_facing_right ? EAST : WEST;
	ray->ray_angle = r->ray_angle;
	ray->is_ray_facing_down = r->is_ray_facing_down;
	ray->is_ray_facing_up = r->is_ray_facing_up;
	ray->is_ray_facing_left = r->is_ray_facing_left;
	ray->is_ray_facing_right = r->is_ray_facing_right;
}