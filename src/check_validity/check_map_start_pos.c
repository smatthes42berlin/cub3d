#include "cub3d.h"


int	check_exactly_one_start_pos(t_parse_state *parse_state)
{
	int	num_start_pos;
	int	height;
	int	width;

	height = 0;
	num_start_pos = 0;
	while (height < parse_state->map_parse.max_height_org)
	{
		width = 0;
		while (width < parse_state->map_parse.max_width_org)
		{
			if (ft_str_chr_index("NWSE",
									parse_state->map_parse.org_rect[height][width]) >= 0)
				get_start_pos(parse_state, height, width, &num_start_pos);
			width++;
		}
		height++;
	}
	if (num_start_pos == 0)
		parse_state->map_parse.no_start_pos = true;
	if (num_start_pos > 1)
		parse_state->map_parse.multi_start_pos = true;
	return (0);
}

int	get_start_pos(t_parse_state *parse_state, int height, int width,
		int *num_start_pos)
{
	parse_state->map_parse.start_pos[0] = height;
	parse_state->map_parse.start_pos[1] = width;
	if (parse_state->map_parse.org_rect[height][width] == 'N')
		parse_state->map_parse.start_orient = 'N';
	if (parse_state->map_parse.org_rect[height][width] == 'S')
		parse_state->map_parse.start_orient = 'S';
	if (parse_state->map_parse.org_rect[height][width] == 'W')
		parse_state->map_parse.start_orient = 'W';
	if (parse_state->map_parse.org_rect[height][width] == 'E')
		parse_state->map_parse.start_orient = 'E';
	(*num_start_pos)++;
	return (0);
}
