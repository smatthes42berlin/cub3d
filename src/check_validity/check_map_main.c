#include "cub3d.h"

int	check_map_validity(t_parse_state *parse_state)
{
	if (!parse_state->map_parse.org_rect)
		return (0);
	if (parse_state->map_parse.max_height_org
		* parse_state->map_parse.max_width_org > MAP_SIZE_LIMIT_FLOOD_FILL)
		return (set_bool_field(&(parse_state->map_parse.over_size_limit), true,
				0));
	print_map(parse_state->map_parse.org_rect,
			parse_state->map_parse.max_width_org,
			parse_state->map_parse.max_height_org);
	check_unknown_characters(parse_state);
	check_exactly_one_start_pos(parse_state);
	// if (parse_state->map_parse.no_start_pos
	// 	|| parse_state->map_parse.multi_start_pos
	// 	|| parse_state->map_parse.unknown_char)
	// 	return (0);
	printf("\n\nbefore filling flood\n\n");
	// flood_fill_rec(parse_state);
	// flood_fill_it(parse_state);
	flood_fill_rec_lim(parse_state);
	printf("\n\nfilled the flood\n\n");
	// only create reachable map, when map is valid
	// shrink map to reachable part for use in program
	// reset values from flood fill to org
	return (0);
}
