#include "cub3d.h"

int	adjust_reachable_map(t_parse_state *parse_state, int height, int width)
{
	if (width < parse_state->map_parse.reachable_width_min)
		parse_state->map_parse.reachable_width_min = width;
	if (width > parse_state->map_parse.reachable_width_max)
		parse_state->map_parse.reachable_width_max = width;
	if (height < parse_state->map_parse.reachable_height_min)
		parse_state->map_parse.reachable_height_min = height;
	if (height > parse_state->map_parse.reachable_height_max)
		parse_state->map_parse.reachable_height_max = height;
	return (0);
}

int	check_map_not_closed(t_parse_state *parse_state, int height, int width)
{
	if (parse_state->map_parse.org_rect[height][width] == ' '
		|| parse_state->map_parse.org_rect[height][width] == '-')
		set_bool_field(&(parse_state->map_parse.not_closed), true, 0);
	if (height + 1 == parse_state->map_parse.max_height_org || height == 0)
		set_bool_field(&(parse_state->map_parse.not_closed), true, 0);
	if (width + 1 == parse_state->map_parse.max_width_org || width == 0)
		set_bool_field(&(parse_state->map_parse.not_closed), true, 0);
	return (0);
}
