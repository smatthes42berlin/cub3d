#include "cub3d.h"

t_draw_line	initialize_line_draw(t_line *line)
{
	t_draw_line	dl;

	dl.x = line->start_x;
	dl.y = line->start_y;
	dl.delta_x = abs(line->end_x - dl.x);
	if (dl.x < line->end_x)
		dl.step_x = 1;
	else
		dl.step_x = -1;
	dl.delta_y = -abs(line->end_y - dl.y);
	if (dl.y < line->end_y)
		dl.step_y = 1;
	else
		dl.step_y = -1;
	dl.error = dl.delta_x + dl.delta_y;
	return (dl);
}

void	draw_line_on_image(int *addr, t_line *line)
{
	t_draw_line	dl;

	dl = initialize_line_draw(line);
	while (true)
	{
		if (dl.x >= 0 && dl.x < line->width && dl.y >= 0 && dl.y < line->height)
			addr[dl.y * line->width + dl.x] = line->color;
		if (dl.x == line->end_x && dl.y == line->end_y)
			break ;
		dl.error2 = 2 * dl.error;
		if (dl.error2 >= dl.delta_y)
		{
			if (dl.x == line->end_x)
				break ;
			dl.error += dl.delta_y;
			dl.x += dl.step_x;
		}
		if (dl.error2 <= dl.delta_x)
		{
			if (dl.y == line->end_y)
				break ;
			dl.error += dl.delta_x;
			dl.y += dl.step_y;
		}
	}
}
