#include "cub3d.h"

int	handle_optn(t_parse_state *parse_state, t_optn_parse *optn)
{
	printf("name %s\n", optn->identifier);
	if (optn_not_def_map_not_started(parse_state, optn))
		optn->line_in_map_file = (char *)(parse_state->cur_line->content);
	else if (optn_alr_def_map_not_started(parse_state, optn))
		optn->multi_def = true;
	else if (map_already_ended(parse_state))
		parse_state->defs_after_map_found = true;
	else
		throw_error_gen(1,
						"Not handled exception for option state parsing map file!",
						true);
	go_to_next_line(parse_state);
	return (0);
}
