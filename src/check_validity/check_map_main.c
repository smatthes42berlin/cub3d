#include "cub3d.h"

int	check_map_validity(t_parse_state *parse_state)
{
	// define size limit for map
	if (!parse_state->map_parse.org_rect)
		return (0);
	if (parse_state->map_parse.max_height_org
		* parse_state->map_parse.max_width_org > MAP_SIZE_LIMIT_FLOOD_FILL)
	{
		parse_state->map_parse.over_size_limit = true;
		return (0);
	}
	check_unknown_characters(parse_state);
	check_exactly_one_start_pos(parse_state);
	if (parse_state->map_parse.no_start_pos
		|| parse_state->map_parse.multi_start_pos
		|| parse_state->map_parse.unknown_char)
		return (0);
	flood_fill(parse_state);
	// only create reachable map, when map is valid
	// shrink map to reachable part for use in program
	// reset values from flood fill to org
	parse_state++;
	return (0);
}
