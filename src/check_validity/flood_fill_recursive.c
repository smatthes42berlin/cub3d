#include "cub3d.h"

int	flood_fill(t_parse_state *parse_state)
{
	int	start_width;
	int	start_height;

	start_height = parse_state->map_parse.start_pos[0];
	start_width = parse_state->map_parse.start_pos[1];
	parse_state->map_parse.reachable_width_min = start_width;
	parse_state->map_parse.reachable_width_max = start_width;
	parse_state->map_parse.reachable_height_min = start_height;
	parse_state->map_parse.reachable_height_max = start_height;
	parse_state->map_parse.org_rect[start_height][start_width] = '0';
	flood_check(parse_state, start_height, start_width);
	return (0);
}

int	flood_check(t_parse_state *parse_state, int height, int width)
{
	if (height + 1 > parse_state->map_parse.max_height_org || height < 0)
		return (0);
	if (width + 1 > parse_state->map_parse.max_width_org || width < 0)
		return (0);
	if (parse_state->map_parse.org_rect[height][width] == 'X'
		|| parse_state->map_parse.org_rect[height][width] == '1')
		return (0);
	if (parse_state->map_parse.org_rect[height][width] == '0')
	{
		parse_state->map_parse.org_rect[height][width] = 'X';
		flood_check(parse_state, height + 1, width);
		flood_check(parse_state, height - 1, width);
		flood_check(parse_state, height, width + 1);
		flood_check(parse_state, height, width - 1);
	}
	check_map_not_closed(parse_state, height, width);
	adjust_reachable_map(parse_state, height, width);
	return (0);
}

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
	if (parse_state->map_parse.org_rect[height][width] == ' ')
		parse_state->map_parse.not_closed = true;
	if (height + 1 == parse_state->map_parse.max_height_org || height == 0)
		parse_state->map_parse.not_closed = true;
	if (width + 1 == parse_state->map_parse.max_width_org || width == 0)
		parse_state->map_parse.not_closed = true;
	return (0);
}

