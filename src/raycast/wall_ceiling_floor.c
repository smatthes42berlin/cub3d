#include "cub3d.h"

void	draw_floor_and_ceiling(t_main_data *data, t_wall *w, int *i)
{
	u_int32_t	ceiling_color;
	int			y;
	u_int32_t	floor_color;

	ceiling_color = convert_rgb_to_hex(data->map.color_ceiling);
	y = 0;
	while (y < w->wall_top_pixel)
	{
		data->color_buffer[(WINDOW_WIDTH * y) + *i] = ceiling_color;
		y++;
	}
	floor_color = convert_rgb_to_hex(data->map.color_floor);
	y = w->wall_bottom_pixel;
	while (y < WINDOW_HEIGHT)
	{
		data->color_buffer[(WINDOW_WIDTH * y) + *i] = floor_color;
		y++;
	}
}

void	calculate_wall_size(t_main_data *data, t_ray *rays, t_wall *w, int *i)
{
	w->perp_distance = rays[(*i)].distance * cos(rays[(*i)].ray_angle
			- data->player.rotation_angle);
	w->distance_proj_plane = (WINDOW_WIDTH / 2) / tan(data->fov_angle / 2);
	w->projected_wall_height = (TILE_SIZE / w->perp_distance)
		* w->distance_proj_plane;
	w->wall_strip_height = w->projected_wall_height;
	w->wall_top_pixel = (WINDOW_HEIGHT / 2) - (w->wall_strip_height / 2);
	if (w->wall_top_pixel < 0)
		w->wall_top_pixel = 0;
	else
		w->wall_top_pixel = w->wall_top_pixel;
	w->wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (w->wall_strip_height / 2);
	if (w->wall_bottom_pixel > WINDOW_HEIGHT)
		w->wall_bottom_pixel = WINDOW_HEIGHT;
	else
		w->wall_bottom_pixel = w->wall_bottom_pixel;
}

void	calculating_wall_offset(t_ray *ray, t_render_wall *rw)
{
	if (ray->was_hit_vertical)
	{
		if (ray->is_ray_facing_right)
			rw->texture_offset_x = (int)ray->wall_hit_y % TILE_SIZE;
		else
			rw->texture_offset_x = TILE_SIZE - 1 - ((int)ray->wall_hit_y
					% TILE_SIZE);
	}
	else
	{
		if (ray->is_ray_facing_up)
			rw->texture_offset_x = (int)ray->wall_hit_x % TILE_SIZE;
		else
			rw->texture_offset_x = TILE_SIZE - 1 - ((int)ray->wall_hit_x
					% TILE_SIZE);
	}
}

void	render_wall_side(t_main_data *data, t_ray *ray, t_wall *w, int i)
{
	int				y;
	t_render_wall	rw;
	int				index;

	rw.tex = ray->hit_side;
	calculating_wall_offset(ray, &rw);
	y = w->wall_top_pixel;
	while (y < w->wall_bottom_pixel)
	{
		rw.distance_from_top = y + (w->wall_strip_height / 2) - (WINDOW_HEIGHT
				/ 2);
		rw.texture_offset_y = rw.distance_from_top * ((float)(rw.tex)->height
				/ w->wall_strip_height);
		index = (rw.tex->width * (rw.texture_offset_y % rw.tex->height))
			+ rw.texture_offset_x % rw.tex->width;
		rw.texel_color = rw.tex->mem[index];
		data->color_buffer[(WINDOW_WIDTH * y) + i] = rw.texel_color;
		y++;
	}
}

void	generate_3d_projection(t_main_data *data, t_ray *rays)
{
	t_wall	w;
	int		i;

	i = 0;
	while (i < data->num_rays)
	{
		calculate_wall_size(data, rays, &w, &i);
		draw_floor_and_ceiling(data, &w, &i);
		render_wall_side(data, &rays[i], &w, i);
		i++;
	}
}
