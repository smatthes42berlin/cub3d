#include "cub3d.h"

bool	optn_not_def_map_not_started(t_parse_state *parse_state,
									t_optn_parse *optn)
{
	return (!optn->line_in_map_file && !parse_state->map_parse.started);
}

bool	optn_alr_def(t_optn_parse *optn)
{
	return (optn->line_in_map_file);
}

bool	map_already_ended(t_parse_state *parse_state)
{
	return (parse_state->map_parse.ended);
}

int	go_to_next_line(t_parse_state *parse_state)
{
	parse_state->cur_line = parse_state->cur_line->next;
	get_cur_line_trimmed(parse_state);
	return (0);
}

int	get_cur_line_trimmed(t_parse_state *parse_state)
{
	free(parse_state->cur_line_trimmed);
	parse_state->cur_line_trimmed = NULL;
	if (!parse_state->cur_line)
		return (0);
	if (ft_strtrim_int(parse_state->cur_line->content, " \n\v\t\f\r",
			&(parse_state->cur_line_trimmed)))
		throw_error_sys_call((t_error_ms){errno, ERROR_MALLOC,
				"trying to trim cur line of map file"}, true);
	return (0);
}
