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
		set_bool_field(&(parse_state->map_parse.no_start_pos), true, 0);
	if (num_start_pos > 1)
		set_bool_field(&(parse_state->map_parse.multi_start_pos), true, 0);
	return (0);
}

int	get_start_pos(t_parse_state *parse_state, int height, int width,
		int *num_start_pos)
{
	parse_state->map_parse.start_pos[0] = height;
	parse_state->map_parse.start_pos[1] = width;
	if (parse_state->map_parse.org_rect[height][width] == 'N')
		set_start_pos_n_angle(parse_state, 'N', 1.5 * PI);
	if (parse_state->map_parse.org_rect[height][width] == 'S')
		set_start_pos_n_angle(parse_state, 'S', 0.5 * PI);
	if (parse_state->map_parse.org_rect[height][width] == 'W')
		set_start_pos_n_angle(parse_state, 'W', 1.0 * PI);
	if (parse_state->map_parse.org_rect[height][width] == 'E')
		set_start_pos_n_angle(parse_state, 'E', 0.0);
	(*num_start_pos)++;
	return (0);
}

int	set_start_pos_n_angle(t_parse_state *parse_state, char orient, float angle)
{
	parse_state->map_parse.start_orient = orient;
	parse_state->map_parse.rotation_angle = angle;
	return (0);
}
