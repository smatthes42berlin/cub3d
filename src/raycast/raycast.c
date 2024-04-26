/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:00:29 by fszendzi          #+#    #+#             */
/*   Updated: 2024/04/18 15:16:51 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycast(t_raycast *r, float ray_angle)
{
	r->ray_angle = normalize_angle(ray_angle);
	r->is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	r->is_ray_facing_up = !r->is_ray_facing_down;
	r->is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	r->is_ray_facing_left = !r->is_ray_facing_right;
}

void	cast_ray(t_main_data *data, t_ray *rays, float ray_angle, int strip_id)
{
	t_raycast	r;
	float		horz_hit_distance;
	float		vert_hit_distance;

	init_raycast(&r, ray_angle);
	cast_horizontal_ray(data, &r);
	cast_vertical_ray(data, &r);
	if (r.found_horz_wall_hit)
	{
		horz_hit_distance = distance_between_points(data->player.x,
				data->player.y, r.horz_wall_hit_x, r.horz_wall_hit_y);
	}
	else
		horz_hit_distance = FLT_MAX;
	if (r.found_vert_wall_hit)
		vert_hit_distance = distance_between_points(data->player.x,
				data->player.y, r.vert_wall_hit_x, r.vert_wall_hit_y);
	else
		vert_hit_distance = FLT_MAX;
	if (vert_hit_distance < horz_hit_distance)
		update_ray_with_vertical_hit(&rays[strip_id], &r, vert_hit_distance);
	else
		update_ray_with_horizontal_hit(&rays[strip_id], &r, horz_hit_distance);
}

void	cast_all_rays(t_main_data *data, t_ray *rays)
{
	float	ray_angle;
	int		strip_id;

	ray_angle = data->player.rotation_angle - (FOV_ANGLE / 2);
	strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		cast_ray(data, rays, ray_angle, strip_id);
		strip_id++;
		ray_angle += FOV_ANGLE / NUM_RAYS;
	}
}
