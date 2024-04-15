#include "cub3d.h"

void fill_color_buffer(u_int32_t color, u_int32_t *color_buffer)
{
	int x = 0;
    while (x < WINDOW_WIDTH)
	{
		int y = 0;
		while (y < WINDOW_HEIGHT)
		{
			
			color_buffer[(WINDOW_WIDTH * y) + x] = color;
			y++;
		}
		x++;
    }
}