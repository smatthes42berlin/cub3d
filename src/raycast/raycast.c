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

void cast_ray(t_main_data *data, t_ray *rays, float ray_angle, int strip_id)
{
	ray_angle = normalize_angle(ray_angle);

	int is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	int is_ray_facing_up = !is_ray_facing_down;

	int is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	int is_ray_facing_left = !is_ray_facing_right;

	////////////////////////////////////////
	/// HORIZONTAL GRID INTERSECTION CODE
	////////////////////////////////////////

	float xintercept;
	float yintercept;

	float xstep;
	float ystep;

	int found_horz_wall_hit = FALSE;
	float horz_wall_hit_x = 0;
	float horz_wall_hit_y = 0;
	int horz_wall_content = 0;

	yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += is_ray_facing_down ? TILE_SIZE : 0;

	xintercept = data->player.x + (yintercept - data->player.y) / tan(ray_angle);

	ystep = TILE_SIZE;
	ystep *= is_ray_facing_up ? -1 : 1;

	xstep = TILE_SIZE / tan(ray_angle);
	xstep *= (is_ray_facing_left && xstep > 0) ? -1 : 1;
	xstep *= (is_ray_facing_right && xstep < 0) ? -1 : 1;

	float next_horz_touch_x = xintercept;
	float next_horz_touch_y = yintercept;

	while (next_horz_touch_x >= 0 && next_horz_touch_x <= WINDOW_WIDTH && next_horz_touch_y >= 0 && next_horz_touch_y <= WINDOW_HEIGHT)
	{
		float x_to_check = next_horz_touch_x;
		float y_to_check = next_horz_touch_y + (is_ray_facing_up ? -1 : 0);

		if (map_has_wall_at(data, x_to_check, y_to_check))
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			horz_wall_content = data->map.map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)] -'0';
			found_horz_wall_hit = TRUE;
			break;
		}
		else
		{
			next_horz_touch_x += xstep;
			next_horz_touch_y += ystep;
		}
	}

	////////////////////////////////////////
	/// VERTICAL GRID INTERSECTION CODE
	////////////////////////////////////////

	int found_vert_wall_hit = FALSE;
	float vert_wall_hit_x = 0;
	float vert_wall_hit_y = 0;
	int vert_wall_content = 0;

	xintercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += is_ray_facing_right ? TILE_SIZE : 0;

	yintercept = data->player.y + (xintercept - data->player.x) * tan(ray_angle);

	xstep = TILE_SIZE;
	xstep *= is_ray_facing_left ? -1 : 1;

	ystep = TILE_SIZE * tan(ray_angle);
	ystep *= (is_ray_facing_up && ystep > 0) ? -1 : 1;
	ystep *= (is_ray_facing_down && ystep < 0) ? -1 : 1;

	float next_vert_touch_x = xintercept;
	float next_vert_touch_y = yintercept;

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= WINDOW_WIDTH && next_vert_touch_y >= 0 && next_vert_touch_y <= WINDOW_HEIGHT)
	{
		float x_to_check = next_vert_touch_x + (is_ray_facing_left ? -1 : 0);
		float y_to_check = next_vert_touch_y;

		if (map_has_wall_at(data, x_to_check, y_to_check))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			vert_wall_content = data->map.map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)] - '0';
			found_vert_wall_hit = TRUE;
			break;
		}
		else
		{
			next_vert_touch_x += xstep;
			next_vert_touch_y += ystep;
		}
	}

	float horz_hit_distance = found_horz_wall_hit
		? distance_between_points(data->player.x, data->player.y, horz_wall_hit_x, horz_wall_hit_y)
		: FLT_MAX;

	float vert_hit_distance = found_vert_wall_hit
		? distance_between_points(data->player.x, data->player.y, vert_wall_hit_x, vert_wall_hit_y)
		: FLT_MAX;

	if (vert_hit_distance < horz_hit_distance)
	{
		rays[strip_id].distance = vert_hit_distance;
		rays[strip_id].wall_hit_x = vert_wall_hit_x;
		rays[strip_id].wall_hit_y = vert_wall_hit_y;
		rays[strip_id].wall_hit_content = vert_wall_content;	
		rays[strip_id].was_hit_vertical = TRUE;
		rays[strip_id].hit_side = (is_ray_facing_right) ? EAST : WEST;

	}
	else
	{
		rays[strip_id].distance = horz_hit_distance;
		rays[strip_id].wall_hit_x = horz_wall_hit_x;
		rays[strip_id].wall_hit_y = horz_wall_hit_y;
		rays[strip_id].wall_hit_content = horz_wall_content;	
		rays[strip_id].was_hit_vertical = FALSE;
		rays[strip_id].hit_side = (is_ray_facing_down) ? SOUTH : NORTH;

	}
	rays[strip_id].ray_angle = ray_angle;
	rays[strip_id].is_ray_facing_down = is_ray_facing_down;
	rays[strip_id].is_ray_facing_up = is_ray_facing_up;
	rays[strip_id].is_ray_facing_left = is_ray_facing_left;
	rays[strip_id].is_ray_facing_right = is_ray_facing_right;
}

void cast_all_rays(t_main_data *data, t_ray *rays)
{
	float ray_angle = data->player.rotation_angle - (FOV_ANGLE / 2);

	int strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		cast_ray(data, rays, ray_angle, strip_id);
		strip_id++;
		ray_angle += FOV_ANGLE / NUM_RAYS;
	}
}


	
