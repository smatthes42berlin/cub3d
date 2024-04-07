#include "cub3d.h"

int	handle_optn(t_parse_state *parse_state, t_optn_parse *optn)
{
	if (optn_not_def_map_not_started(parse_state, optn))
	{
		optn->line_in_map_file = ft_strdup(((char *)(parse_state->cur_line_trimmed)
					+ ft_strlen(optn->identifier)));
		if (!optn->line_in_map_file)
			throw_error_sys_call((t_error_ms){errno, ERROR_MALLOC,
					"Cannot duplicate line of file!"}, true);
	}
	else if (optn_alr_def(optn))
	{
		optn->multi_def = true;
		if (map_already_ended(parse_state))
			parse_state->defs_after_map_found = true;
		parse_state->map_file_valid = false;
	}
	else
		throw_error_gen(1,
						"Not handled exception for option state parsing map file!",
						true);
	go_to_next_line(parse_state);
	return (0);
}
