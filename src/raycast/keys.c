#include "cub3d.h"

void	calculate_new_position(t_main_data *data, int key, float *new_x,
		float *new_y)
{
	float	move_step;
	float	angle;

	move_step = STRAIGHT_MOVEMENT;
	angle = data->player.rotation_angle;
	if (key == 'a')
	{
		*new_x += sin(angle) * move_step;
		*new_y -= cos(angle) * move_step;
	}
	else if (key == 'd')
	{
		*new_x -= sin(angle) * move_step;
		*new_y += cos(angle) * move_step;
	}
	else if (key == 'w')
	{
		*new_x += cos(angle) * move_step;
		*new_y += sin(angle) * move_step;
	}
	else if (key == 's')
	{
		*new_x -= cos(angle) * move_step;
		*new_y -= sin(angle) * move_step;
	}
}

void	update_player_position(t_main_data *data, int key)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x;
	new_y = data->player.y;
	calculate_new_position(data, key, &new_x, &new_y);
	if (!check_collision(data, new_x, new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	update_player_rotation(t_main_data *data, int key)
{
	if (key == 65361)
	{
		data->player.rotation_angle -= ROTATION_MOVEMENT;
		if (data->player.rotation_angle < 0)
			data->player.rotation_angle += TWO_PI;
	}
	else if (key == 65363)
	{
		data->player.rotation_angle += ROTATION_MOVEMENT;
		if (data->player.rotation_angle >= TWO_PI)
			data->player.rotation_angle -= TWO_PI;
	}
}

int	keys(int key, void *param)
{
	t_main_data	*data;

	data = (t_main_data *)param;
	if (key == 65307)
	{
		destroy_window(data);
		exit(0);
	}
	update_player_position(data, key);
	update_player_rotation(data, key);
	return (0);
}
