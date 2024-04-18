/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:00:12 by fszendzi          #+#    #+#             */
/*   Updated: 2024/04/15 15:00:15 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keys(int key, void *param)
{
	t_main_data	*data;
	float		new_player_x;
	float		new_player_y;

	data = (t_main_data *)param;
	new_player_x = data->player.x;
	new_player_y = data->player.y;
	if (key == 65307)
	{
		destroy_window(data);
		exit(0);
	}
	if (key == 'a') // Move left
	{
		new_player_x += sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
		new_player_y -= cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}
	if (key == 'd') // Move right
	{
		new_player_x -= sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
		new_player_y += cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}
	if (key == 'w') // Move forward
	{
		new_player_x += cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
		new_player_y += sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}
	if (key == 's') // Move backward
	{
		new_player_x -= cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
		new_player_y -= sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}
	if (key == 65361) // Rotate Left
	{
		data->player.rotation_angle -= ROTATION_MOVEMENT;
		if (data->player.rotation_angle < 0)
			data->player.rotation_angle += TWO_PI;
	}
	if (key == 65363) // Rotate Right
	{
		data->player.rotation_angle += ROTATION_MOVEMENT;
		if (data->player.rotation_angle >= TWO_PI)
			data->player.rotation_angle -= TWO_PI;
	}
	if (!map_has_wall_at(new_player_x, new_player_y))
	{
		data->player.x = new_player_x;
		data->player.y = new_player_y;
	}
	return (0);
}
