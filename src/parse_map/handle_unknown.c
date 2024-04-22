#include "cub3d.h"

int	handle_unknown(t_parse_state *parse_state)
{
	if (map_already_ended(parse_state))
		set_bool_field(&(parse_state->defs_after_map_found), true, 0);
	set_bool_field(&(parse_state->unknown_lines_found), true, 0);
	go_to_next_line(parse_state);
	return (0);
}
