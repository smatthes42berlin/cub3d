#include "cub3d.h"

int	create_reachable_map(t_parse_state *parse_state)
{
	if (subarr_arr_str(parse_state->map_parse.org_rect,
			(t_subarr_arr_str){
			parse_state->map_parse.reachable_height_min - 1,
			parse_state->map_parse.reachable_height_max + 2,
			parse_state->map_parse.reachable_width_min - 1,
			parse_state->map_parse.reachable_width_max + 2,
		}, &(parse_state->map_parse.reachable_rect)))
		throw_error_sys_call_parse((t_error_ms){errno, ERROR_MALLOC,
			"Cannot copy reachable map array!"}, parse_state, true);
	return (0);
}
