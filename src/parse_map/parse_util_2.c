#include "cub3d.h"

bool	is_no(t_parse_state *parse_state)
{
	return (compare_line(parse_state, "NO "));
}
bool	is_so(t_parse_state *parse_state)
{
	return (compare_line(parse_state, "SO "));
}
bool	is_we(t_parse_state *parse_state)
{
	return (compare_line(parse_state, "WE "));
}
bool	is_ea(t_parse_state *parse_state)
{
	return (compare_line(parse_state, "EA "));
}

int	go_to_next_line(t_parse_state *parse_state)
{
	parse_state->cur_line = parse_state->cur_line->next;
	get_cur_line_trimmed(parse_state);
	return (0);
}

int	get_cur_line_trimmed(t_parse_state *parse_state)
{
	if (ft_strtrim_int(parse_state->cur_line->content, " \n\v\t\f\r",
			&(parse_state->cur_line_trimmed)))
		throw_error_sys_call((t_error_ms){errno, ERROR_MALLOC,
			"trying to trim cur line of map file"}, true);
	return (0);
}
