#include "cub3d.h"

void	fill_color_buffer(t_main_data *data, u_int32_t color)
{
	int	x;
	int	y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			data->color_buffer[(WINDOW_WIDTH * y) + x] = color;
			y++;
		}
		x++;
	}
}
