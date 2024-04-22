/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:00:12 by fszendzi          #+#    #+#             */
/*   Updated: 2024/04/18 15:16:59 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int keys(int key, void *param)
{
    t_main_data *data = (t_main_data *)param;
    float new_player_x = data->player.x;
    float new_player_y = data->player.y;
    float buffer = 3;

    if (key == 65307) {
        destroy_window(data);
        exit(0);
    }

    // Calculate new potential positions based on input
    if (key == 'a') {  // Move left
        new_player_x += sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
        new_player_y -= cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
    } else if (key == 'd') {  // Move right
        new_player_x -= sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
        new_player_y += cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
    } else if (key == 'w') {  // Move forward
        new_player_x += cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
        new_player_y += sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
    } else if (key == 's') {  // Move backward
        new_player_x -= cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
        new_player_y -= sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
    }

    // Rotation commands
    if (key == 65361) {  // Rotate Left
        data->player.rotation_angle -= ROTATION_MOVEMENT;
        data->player.rotation_angle = data->player.rotation_angle < 0 ? data->player.rotation_angle + TWO_PI : data->player.rotation_angle;
    } else if (key == 65363) {  // Rotate Right
        data->player.rotation_angle += ROTATION_MOVEMENT;
        data->player.rotation_angle = data->player.rotation_angle >= TWO_PI ? data->player.rotation_angle - TWO_PI : data->player.rotation_angle;
    }

    // BUFFER ZONE CHECK
	int angle = 0;
    while (angle < 360)
	{
        float rad = angle * (PI / 180);
        float check_x = new_player_x + cos(rad) * buffer;
        float check_y = new_player_y + sin(rad) * buffer;
        if (map_has_wall_at(data, check_x, check_y))
            return 0;
		angle += 30;
    }
    data->player.x = new_player_x;
    data->player.y = new_player_y;

    return 0;
}

