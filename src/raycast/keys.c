#include "cub3d.h"

int keys(int key, void *param)
{
    t_main_data *data = (t_main_data *)param;

	float new_player_x = data->player.x;
    float new_player_y = data->player.y;
    if (key == 65307)
    {
        destroy_window(data);
        exit(0);
    }
	if (key == 'a') // Strafe left
	{
		new_player_x += sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
		new_player_y -= cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}
	if (key == 'd') // Strafe right
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

	if (key == 65361) // Left
	{
    	data->player.rotation_angle -= ROTATION_MOVEMENT;
    	if (data->player.rotation_angle < 0)
			data->player.rotation_angle += TWO_PI;
    	//data->player.delta_x = cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
    	//data->player.delta_y = sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}
	if (key == 65363) // Right
	{
    	data->player.rotation_angle += ROTATION_MOVEMENT;
    	if (data->player.rotation_angle >= TWO_PI)
			data->player.rotation_angle -= TWO_PI;
    	//data->player.delta_x = cos(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
    	//data->player.delta_y = sin(data->player.rotation_angle) * STRAIGHT_MOVEMENT;
	}

	if (!map_has_wall_at(new_player_x, new_player_y))
	{
		data->player.x = new_player_x;
		data->player.y = new_player_y;
	}
    return 0;
}