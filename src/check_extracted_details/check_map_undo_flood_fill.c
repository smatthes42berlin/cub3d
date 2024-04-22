#include "cub3d.h"

int	undo_flood_fill(t_parse_state *parse_state)
{
	int		*start_pos_o;
	int		height;
	int		width;
	char	start;

	start = parse_state->map_parse.start_orient;
	start_pos_o = parse_state->map_parse.start_pos_o;
	parse_state->map_parse.org_rect[start_pos_o[0]][start_pos_o[1]] = start;
	height = 0;
	while (height < parse_state->map_parse.max_height_org)
	{
		width = 0;
		while (width < parse_state->map_parse.max_width_org)
		{
			if (parse_state->map_parse.org_rect[height][width] == FLOOD_CHAR)
				parse_state->map_parse.org_rect[height][width] = '0';
			width++;
		}
		height++;
	}
	return (0);
}
