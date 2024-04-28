#include "cub3d.h"

void	draw_player_direction(t_main_data *data, int *addr)
{
	int		scaled_line_length;
	t_line	line;

	line.width = WINDOW_WIDTH;
	line.height = WINDOW_HEIGHT;
	line.color = 0xFFFF00;
	scaled_line_length = 30 * data->scale_factor;
	line.start_x = (data->player.x + data->player.size / 2)
		* data->scale_factor;
	line.start_y = (data->player.y + data->player.size / 2)
		* data->scale_factor;
	line.end_x = line.start_x + cos(data->player.rotation_angle)
		* scaled_line_length;
	line.end_y = line.start_y + sin(data->player.rotation_angle)
		* scaled_line_length;
	draw_line_on_image(addr, &line);
}

void	draw_player(t_main_data *data, int *addr)
{
	t_draw_player	dp;

	dp.y = 0;
	dp.scaled_size = data->player.size * data->scale_factor;
	while (dp.y < dp.scaled_size)
	{
		dp.x = 0;
		while (dp.x < dp.scaled_size)
		{
			dp.scaled_x = data->player.x * data->scale_factor + dp.x;
			dp.scaled_y = data->player.y * data->scale_factor + dp.y;
			if (dp.scaled_x >= 0 && dp.scaled_x < WINDOW_WIDTH
				&& dp.scaled_y >= 0 && dp.scaled_y < WINDOW_HEIGHT)
			{
				dp.pixel_index = dp.scaled_y * WINDOW_WIDTH + dp.scaled_x;
				addr[dp.pixel_index] = data->player.color;
			}
			dp.x++;
		}
		dp.y++;
	}
}
