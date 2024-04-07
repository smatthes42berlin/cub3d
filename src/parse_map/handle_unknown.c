#include "cub3d.h"

int	handle_unknown(t_parse_state *parse_state)
{
	printf("unknown!\n");
	if (map_already_ended(parse_state))
		parse_state->defs_after_map_found = true;
	parse_state->unknown_lines_found = true;
	parse_state->map_file_valid = false;
	go_to_next_line(parse_state);
	return (0);
}
